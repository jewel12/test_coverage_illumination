# coding: utf-8
# usage: ruby coverage_sender.rb SERIAL_PORT < COVERAGE

require 'serialport'

port = ARGV[0]
coverage = STDIN.read.to_i
SerialPort.open(port, 9600) do |sp|
  sleep(2)
  sp.write([coverage].pack('c'))
end
