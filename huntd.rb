#!/usr/bin/env ruby

require 'socket'

class HuntServer

  def initialize(port)
    @port = port
    @clients = []
  end

  def generate_map
  end

  def send_map(clientaddr)
    map = generate_map
    #TODO: writeme
  end
  
  def getclientaddr(packet)
    #TODO: writeme
    "127.0.0.1"
  end

  def process(packet)

    # parse packet
    cmd = packet[0] 
    clientaddr = getclientaddr(packet)

    # do something with the command
    case cmd
      when "STARTGAME"
        puts "Registering a new client @ #{clientaddr}"
        @clients.push(clientaddr)
      when "GETMAP"
        puts "Sending a map to #{clientaddr}"
        send_map(clientaddr)
      else
        puts "Unknown command #{cmd}"
    end
  end

  def start
    @socket = UDPSocket.new
    @socket.bind('localhost', @port) 
    while true
      packet = @socket.recvfrom(1024) # max bytes to recieve
      self.process(packet)
    end
  end
end

server = HuntServer.new(31337)
server.start

