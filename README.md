# What is Nucleus?
Nucleus is an implementation of a domain-based certificate authority system. It provides access to a server that can validate requests and store them in its local custom database to be referenced at will. 

### This system offers the following security improvements over the other systems that you typically see in the wild:
__No single points of failure__
If someone were to forge a certificate to a provider like google, they would compromise all of the services that sit inside of the google authentication symbol, effectively taking control of a large portion of your life. With domain-based certificate authorities we get rid of this issue entirely.


## Building Nucleus
Nucleus runs on most OSX and Linux variants and right now only supports 64-bit architectures.

You may be able to get it to compile on other systems with a bit of tweaking, but there is currently not support for that as of now.

Simply run:
`$ make`

## Running Nucleus
To run this with default configurations in place (advanced config coming soon)

 `$ cd src`
 
 `$ ./nucleus-server`

Using any http enabled client you can begin making requests for your local domain and have your traffic encrypted between you and servers within the domain as validated through this CA server.
