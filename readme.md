Bramble
=======

An implementation of a text line based client-server protocol suitable for embedded applications in C++11 and up.

## Why?

- useful for adding a remote interface to a "device-under-test" (e.g. for ETSI/FCC testing)
- text based, few rules, make it up as you go
- compatible with test documents and generic serial terminal applications
- no code generation tools required
- works with UARTs that are already being used for logging (e.g. ESP32 U0)

## Features

- server implementation
    - portable via `Bramble::Server::Host` interface
- extensible text processing
    - `Bramble::GetOpt` (long and short name option parser)
    - `Bramble::Encoder` (value-to-text functionality)
    - `Bramble::Decoder` (text-to-value functionality)
- header only distribution
    - separate files (`include/bramble.hpp`)
    - single file (`single_include/bramble.hpp`)

## Limitations

- ASCII only
- no C++ client at this time
- no integrity protection, this needs to go on another layer

## Todos

- configurable line endings
- configurable prefix
- C++ client
- translate Bramble::StringView to std::basic_string_view

## Contributing

- Bug reports are welcome
- Not accepting code contributions

## Bramble Protocol

Bramble protocol requires two streams, an input stream from client to server, and an output
stream from server to client. This can work over a UART or be transported by another protocol.

Input and output streams transmit lines of text. The input stream line is terminated by a carriage return (`\r`), the output stream
line is terminated by a carriage return and line feed (`\r\n`). A line is tokenised by whitespace. Tokens can be made to include whitespace by
escaping (`\ `) or by single or double quotes. Consequently, the following characters must always be escaped if they do not appear within quotes: `\\`, `\'`, and `\"`.

The input stream carries only one type of line; the command line.
This can be written either by software or by a human typing into a serial terminal.
The first token on this line is interpreted as the command name, successive tokens are intepreted as arguments.

The command name token shall be any printable characters, but it should follow this pattern:

`^(?<command_name>[a-zA-Z0-9_]+)(#(?<invocation_id>[0-9]+))?$`

- the command_name field shall be one or more alpha-numeric characters, possibly separated by underscore
- the invocation_id field is optional
    - presence is indicated by leading `#` character
    - one or more numeric characters shall follow

A command name token that does not match this pattern shall be treated as a literal (e.g. "some-command#" shall lookup a handler registered for "some-command#").

The invocation_id field is useful for clients to correlate successive commands and responses.

A server shall not acknowledge a line with zero tokens.

The output stream carries several different lines which are multiplexed according to a prefix. These lines are:

- "CMD:" command line echo
- "ACK:" positive acknowledge
- "NAK:" negative acknowledge
- "EVT:" asynchronous events
- "LOG:" log messages

Bramble protocol in EBNF:

~~~
line = command | echo | positive_acknowledge | negative_acknowledge | event | log ;

command                 = command_name, [ arguments ], command_end ;
echo                    = "CMD:", command_name, [ arguments ], end ;
positive_acknowledge    = "ACK:", command_name, [ arguments ], end ;
negative_acknowledge    = "NAK:", command_name, error_name, end ;
event                   = "EVT:", event_name, [ arguments ], end ;
log                     = "LOG:", ? all visible characters ? , end ;

command_name = token ;
error_name = token ;
event_name = token ;

arguments = { token };

command_end = "\r" ;
end = "\r\n" ;

(* token should be any printable characters *)
(* tokens are delimited whitespace *)
(* single or double quotes may be used to encapsulate whitespace within a token *)
~~~

### Samples

#### Positive Acknowledge

~~~
generate_cw freq=868100000 dbm=14
~~~
~~~
CMD:generate_cw freq=868100000 dbm=14
ACK:generate_cw
~~~

#### Negative Acknowledge

~~~
generate_lora freq=1000000 dbm=14 sf=12 bw=125000
~~~
~~~
CMD:generate_lora freq=1000000 dbm=14 sf=12 bw=125000
NAK:generate_lora freq_out_of_range
~~~

#### Command with optional invocation identifier

~~~
generate_lora#42 freq=868100000 dbm=14 sf=12 bw=125000
~~~
~~~
CMD:generate_lora#42 freq=868100000 dbm=14 sf=12 bw=125000
ACK:generate_lora#42
~~~

Client side is free to append an identifier here to more reliably pair CMD, ACK, and NAK to a specific command line input.
Bramble::Server will lookup `generate_lora` instead of `generate_lora#42`.

#### Command with different argument types

~~~
send_lora --encoding=hex buffer='make sure to send this message'
~~~
~~~
CMD:send_lora --encoding=hex buffer='make sure to send this message'
ACK:send_lora
~~~

## License

MIT
