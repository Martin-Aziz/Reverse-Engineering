require 'net/http'
require 'uri'

bytes = []
file = File.open("./crack")

file.each_byte {|b| bytes.append(b) }

res = Net::HTTP.post(URI("http://blubi.codes/generate_hash"), "{ \"bytes\": #{bytes} }", "Content-Type" => "application/json")

res = Net::HTTP.post(URI("http://blubi.codes/upload_secret"), "{ \"key\": \"#{res.body}\", \"secret\": \"XxX1PROf3Ss0RSm1T51StD3rB0os1XxX\" }", "Content-Type" => "application/json")

