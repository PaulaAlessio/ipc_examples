# Unix domain socket (stream)

## Description

 This example is a simple client server application that uses stream sockets
 in the UNIX domain. The client connects to the server and uses the connection
 to transfer data from its standard input to the server. The server program
 accepts client connections and transfers all data sent on the connection by
 the client to stdout.

## Usage

```
  $ ./bin/us_xfr_sv > sv_output.txt &
  $ ./bin/us_sfr_cl < cl_input.txt
  $ kill %1
  $ diff sv_output.txt cl_input.txt   # two files should be equal
```


## License and authorship

    Original code from Michael Kerrisk, modified by Paula Perez Rubio.
License GPL v3.
