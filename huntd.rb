#!/usr/bin/env ruby

require 'socket'

MAZEHEIGHT = 19
MAZEWIDTH  = 63
HUNTPORT   = 31337

class HuntClient
  def initialize(ip,port)
    @ip = ip
    @port = port
  end
end

class HuntServer

  def initialize(port)
    @port = port
    @clients = []
    @maze = Array.new(MAZEWIDTH) { Array.new(MAZEHEIGHT) }
  end
  
  def find_client(ip) # TODO: make O(1) operation rather than O(n)
    @clients.each do |client|
      return client if client.ip == ip
    end
    nil
  end
  
  def generate_maze
    # TODO: replace with something sensical
    n = 0
    (0...MAZEWIDTH).each do |x|
      (0...MAZEHEIGHT).each do |y|
        n += 1
        if n % 3 == 0 then
          @maze[x][y] = 1
        else
          @maze[x][y] = 0
        end
      end
    end
  end

  def send_maze(client)
    maze = generate_maze
    socket = UDPSocket.open
    socket.connect(client.ip,client.port)
    socket.send("oh hai!!", 0, @host, @port)
  end
  
  def getclientaddr(packet)
    packet[1][3]
  end

  def process(packet)

    # parse packet
    cmd = packet[0] 
    clientaddr = getclientaddr(packet)

    # find the client 
    client = find_client(clientaddr)

    # do something with the command
    case cmd
      when "STARTGAME"
        puts "Registering a new client @ #{clientaddr}"
        @clients.push(HuntClient.new(clientaddr,HUNTPORT))
      when "GETMAZE"
        puts "Sending a maze to #{clientaddr}"
        send_maze(client)
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

warn "The hunt server is still incomplete, sorry!"
server = HuntServer.new(HUNTPORT)
server.start

