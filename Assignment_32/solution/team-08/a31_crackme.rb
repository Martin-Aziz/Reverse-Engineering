#!/usr/bin/env ruby
require './crackme.rb' # Datei muss im Verzeichnis liegen

if __FILE__ == $0
	CrackMe.nc("./crackme"){
		|crackme| crackme.send_line("1")
		crackme.send_line("9595694924")
		crackme.send_line("5822809")
		puts crackme.get_flag
	}	
end