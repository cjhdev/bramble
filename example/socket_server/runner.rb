#!/usr/bin/env ruby

require "bundler/setup"
require 'minitest/spec'
require 'bramble_client'
require 'open3'
require 'socket'

logger = Logger.new(STDOUT)

client = BrambleClient.new(logger: logger)

describe "demo" do

  describe "echo" do

    it "handles" do

      args = ["one", "two", "three"]

      assert_equal args, client.command("echo", *args)

    end

  end

end

threads = []

Open3.popen3("bin/main") do |stdin, stdout, stderr, wait_thr|

  pid = wait_thr.pid

  stdin.close

  port = Integer(stdout.gets)

  socket = TCPSocket.new "localhost", port

  client.set_output_handler do |line|
    socket.print line
  end

  threads << Thread.new do
    socket.each_line do |line|
      client.input(line)
    end
  end

  threads << Thread.new do
    begin
      stdout.each_line do |line|
        logger.info{"line: #{line.strip}"}
      end
    rescue
    end
    logger.info{"exiting..."}
  end

  Minitest.run

  Process.kill("INT", wait_thr.pid)

end

threads.each(&:join)
