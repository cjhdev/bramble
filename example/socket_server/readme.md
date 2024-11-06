Socket Server Example
=====================

- Bramble::Server::Host is subclassed to communicate over TCP
- `ruby/bramble_client` is used to drive the client side
- `runner.rb` uses minitest to open socket and send commands

## Dependencies

- Ruby and Bundler (system Ruby should be fine, not sure if that comes with Bundler)
- Boost Asio (from apt should be fine)

## Setup

- `make` to build the server side
- `bundle install` to install ruby dependencies

## Running

- `./runner.rb`

