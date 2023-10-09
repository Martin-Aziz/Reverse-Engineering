#!/usr/bin/env ruby
# Helper class to write solutions for crackmes in Ruby.
#
require 'socket'
require 'pty'
require 'io/console'

##
# Class representing a buffer of bytes.
class Buffer
  ##
  # Create a new object.
  # @param [Array<Integer>] ary Contents of the buffer
  def initialize(ary = [])
    @contents = ary
  end

  ##
  # Reverse the contents of the buffer.
  # @return [Buffer] the reversed buffer
  def reverse
    Buffer.new(@contents.reverse)
  end

  ##
  # Append new elements to the buffer.
  # @param [Array<Integer>, Buffer, Integer, String] elements The data to add
  def <<(elements)

    if elements.is_a? String
      @contents << elements.chars.map { |e| e.ord }
    else
      mapped = if !elements.respond_to?(:to_a)
        [elements]
      else
        elements.to_a
      end

      mapped.map! do |e|
        if e.is_a?(String)
          e.ord
        else
          e.to_i
        end
      end
      @contents << mapped
    end

    @contents.flatten!
  end

  ##
  # Convert the buffer into an array.
  # @return [Array<Integer>] The contents as array.
  def to_a
    @contents
  end

  ##
  # Return the buffer in the format uses by the Unix echo
  # command.
  # @return [String] Echo string
  def to_echo
    @contents.map { |e| '\x' + '%02x' % e }.join('')
  end

  ##
  # Convert the buffer into an array.
  # @return [Array<Integer>] The contents as array.
  def to_array
    to_a
  end

  ##
  # Return a string representation.
  # @return [String] String representation
  def to_s
    to_a.map { |e| "0x" + e.to_s(16) }.join(" ")
  end

  ##
  # Return a string representation.
  # @return [String] String representation
  def to_str
    to_s
  end

  ##
  # Return a string representation with the data of the
  # buffer as binary data inside the string.
  # @return [String] Buffer's content
  def to_binary_string
    to_a.map { |e| e.chr }.join
  end

  ##
  # Interpret the Buffer as an integer value in little endian
  # format and return the corresponding integer value.
  # @return [Integer] The buffer as little endian integer
  def to_i
    r = 0
    @contents.each_with_index { |e,i| r += e << (i * 8) }
    r
  end

  ##
  # Append the given value n times to the buffer.
  # @param [Integer] v Value to be added
  # @param [Integer] n Repetitions of the value
  def add(v, n)
    n.times { @contents << v }
  end
end

##
# Object representation of an address.
# The address has 64 bit.
class Address

  ##
  # Create an object by parsing the given string.
  # @param [String] str The string to be parsed into an address
  def self.parse_hex(str)
    # remove 0x
    new_str = str.gsub(/^0x/, '')
    Address.new(new_str.to_i(16))
  end

  ##
  # Create a new object wrapping an address.
  # @param [Integer] value The address as integer
  def initialize(value = 0)
    @value = value
  end

  ##
  # Add a value to this address.
  # @param [Address, Integer, String] other The object to add
  # @return [Address] the result
  def +(other)
    Address.new(@value + other.to_i)
  end

  ##
  # Subtract a value from this address.
  # @param [Address, Integer, String] other The object to subtract
  # @return [Address] the result
  def -(other)
    Address.new(@value - other.to_i)
  end

  ##
  # Multiply the address with a value.
  # @param [Address, Integer, String] other The object to multiply
  # @return [Address] the result
  def *(other)
    Address.new(@value * other.to_i)
  end

  ##
  # Bitwise and of the address.
  # @param [Address, Integer, String] other The object to use
  # @return [Address] the result
  def &(other)
    Address.new(@value & other.to_i)
  end

  ##
  # Align the address on the given boundary.
  # @param [Integer] v Boundary
  # @return [Address] the result
  def align(v)
    a = Address.new(@value)
    a.align! v
    a
  end

  ##
  # Align this address on the given boundary.
  # @param [Integer] v Boundary
  def align!(v)
    @value = @value & (~(v-1))
  end

  ##
  # Convert into a an array of bytes in little endian format.
  # @return [Array<Integer>] Array of bytes representing the address
  def to_a
    [@value].pack('Q').unpack('CCCCCCCC')
  end

  ##
  # Convert the address into a binary string in little endian format.
  # @return [String] Address in little endian format
  def to_binary_string
    to_a.map { |e| e.chr }.join
  end

  ##
  # Return a string representation.
  # @return [String] String representation
  def to_s
    "0x" + @value.to_s(16)
  end

  ##
  # Return a string representation.
  # @return [String] String representation
  def to_str
    to_s
  end

  ##
  # Return the address as an 64bit integer.
  # @return [Integer] The address as integer
  def to_i
    @value
  end

  ##
  # Return the address as an 64bit integer.
  # @return [Integer] The address as integer
  def to_int
    @value
  end

  ##
  # Return the n-th byte of the address-
  # @param [Integer] index The byte to return
  # @return [Integer] The byte at the given index
  def [](index)
    to_a[index]
  end
end

##
# Class to write simple crackmes.
class CrackMe

  ##
  # Initialize the object.
  def initialize()
    @verbose = false
    @delay = 0.5
  end

  ##
  # Enable verbose output.
  def verbose!
    @verbose = true
  end

  ##
  # Set the delay between each interaction.
  # @param [Float] new_delay Delay in secondes
  def delay=(new_delay)
    @delay = new_delay
  end

  ##
  # Get the delay between each interaction.
  # @return [Float] Delay in secondes
  def delay
    @delay = new_delay
  end

  ##
  # Read until the given text is encountered.
  # @param [String] symbol The text to look for in the output
  # @return [String] The read data
  def read_until(symbol)
    result = ""
    loop do
      c = receive()
      print c if @verbose
      result << c
      break if result[-symbol.length..-1] == symbol
    end
    result
  end

  ##
  # Read until the line ends.
  # @return [String] The read data
  def read_line
    result = ""
    loop do
      c = receive()
      print c if @verbose
      result << c
      break if c == "\n"
    end
    result
  end

  ##
  # Read until a flag is encountered
  # @return [String, nil] The flag, if found, otherwise nil
  def get_flag(regex = /(FLAG{.*?})/)
    flag = nil
    loop do
      s = read_line
      if s =~ regex
        flag = $1
        break
      end
    end
    flag
  end

  ##
  # Echo all data received.
  def echo
    loop do
      c = receive()
      break if c.length == 0
      print c
    end
  end

  ##
  # Send a string and sleep.
  # @param [String] str The string to send
  def send_string(str)
    send(str)
    print "-> #{str}\n" if @verbose
    sleep @delay
  end

  ##
  # Send a byte and sleep.
  # @param [Integer] b The byte to send.
  def send_byte(b)
    send(b.chr)
    print "-> #{b.chr}\n" if @verbose
    sleep @delay
  end

  ##
  # Send a line and sleep. A newline character is added to the string.
  # @param [String] str The string to send
  def send_line(str)
    send(str + "\n")
    sleep @delay
  end

  ##
  # Send a buffer and sleep.
  # @param [Buffer] buf The buffer to send
  def send_buffer(buf)
    send_buffer = buf.to_a.flatten.pack('c*')
    send(send_buffer)
    print "-> #{buf.to_s}\n" if @verbose
    sleep @delay
  end

  ##
  # Send an adress and sleep.
  # @param [Adress] address The address to send
  def send_address(address)
    buffer = Buffer.new
    buffer << address
    send_buffer(buffer)
  end

  ##
  # Open a connection and execute the given routine.
  # @param [String] host Host to connect to
  # @param [Integer] port Port to connect to
  # @param [Proc] routine The block to execute
  def self.open(host, port, &routine)
    TCPSocket.open(host, port) do |socket|
      crack_me = CrackMeSocket.new(socket)
      routine.call(crack_me)
    end
  end

  ##
  # Start an executable and interact with it. The interaction happens
  # by running the executable as a network service.
  # @param [String] program Program to start
  # @param [Proc] routine The block to execute
  def self.nc(program, &routine)
    host = "localhost"
    port = "30000"

    puts "Executing #{program} as network service on port #{port}"

	  %x{rm -f /tmp/2way}
    %x{mkfifo /tmp/2way 2>&1 > /dev/null}
	  %x{killall -9 #{program} 2>&1 > /dev/null}
	  %x{killall -9 nc 2>&1 > /dev/null}
	  %x{nc -l #{port} 0</tmp/2way| ./#{program} 1>/tmp/2way &}
	  %x{rm -f /tmp/2way}

    TCPSocket.open(host, port) do |socket|
      crack_me = CrackMeSocket.new(socket)
      routine.call(crack_me)
    end

    %x{killall -9 #{program} 2>&1 > /dev/null}
	  %x{killall -9 nc 2>&1 > /dev/null}
	  %x{rm -f /tmp/2way}
  end

  ##
  # Start an executable and interact with it.
  # @param [String] program Program to start
  # @param [Proc] routine The block to execute
  def self.exe(program, &routine)
    PTY.spawn(program) do |read, write, pid|
      puts "Executing #{program} with PID #{pid}"
      crack_me = CrackMeExe.new(read, write)
      routine.call(crack_me)
    end
  end

  ##
  # Solve a simple, symbolic math equation like 2 + 3.
  # @param [String] s The equation
  # @return [Integer] The solution
  def solve(s)
    s =~ /(.*)([+\-*\/])(.*).*=/

    left = $1.strip.to_i
    right = $3.strip.to_i
    op = $2.strip

    case op
      when '*'
        left * right
      when '+'
        left + right
      when '-'
        left - right
      when '/'
        left / right
      else
        0
    end
  end

def close; end

protected

  ##
  # Send data.
  # @param [String] data Data to send
  def send(data); end

  ##
  # Receive data.
  # @return [String] Data received
  def receive; end

private

  ##
  # Subclass for socket based crackmes.
  class CrackMeSocket < CrackMe

    ##
    # Initialize the object.
    # @param [Socket] socket The socket to use
    def initialize(socket)
      super()
      @socket = socket
    end

    ##
    # Send data to the socket.
    # @param [String] data Data to send
    def send(data)
      @socket.send(data, 0)
    end

    ##
    # Receive data from the socket.
    # @return [String] Data received
    def receive
      @socket.recv(1) # Get one byte from the socket
    end
  end

  ##
  # Subclass for executables instead of sockets.
  class CrackMeExe < CrackMe
      ##
      # Create a new instance.
      # @param [IO] read Read pipe
      # @param [IO] write Write pipe
      def initialize(read, write)
        super()
        @read = read
        @write = write
      end

    ##
    # Send the data to the program.
    # @param [String] data The data to send
    def send(data)
      @write.write(data)
      @write.flush
      @write.ioflush
    end

    ##
    # Receive the data from the program.
    # @return [String] The data to received
    def receive
      begin
        @read.getc
      rescue Errno::EIO => e
        ''
      end
    end

    def close
      @write.close
    end
  end
end
