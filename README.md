# connmap
connmap is an X11 desktop widget that shows location of your current network peers on a world map.
![sample](https://raw.githubusercontent.com/jafarlihi/connmap/master/sample.png?token=AKL72SZ6ZUB4HTXII7GKNWK6PYZPA)

Here's how it looks on my desktop with the default settings:
![desktop](https://raw.githubusercontent.com/jafarlihi/connmap/master/desktop.png?token=AKL72S5HJ6HPGP5PRTAG66K6PYZTG)

## Installation
Clone the repository and run `make install`.

## Dependencies
Build dependencies: xlib, libcairo

Runtime dependencies: `ss` utility of `iproute2` package

## Config
Installation will create `.connmap/connmaprc` in your home directory. Default `connmaprc` looks like this:
```
location_x 20
location_y 500
white true
small true
update_interval 1
```
- location_x/location_y specifies the widget location in your desktop. 

- Setting `white` to false will draw a black map.

- Setting `small` to false will resize widget from 500px/250px to 1000px/500px.

- `update_interval` is seconds the application will sleep for before fetching the updated list of network connections.
## Limitations
- Only IPv4 is supported.

- Only country geolocation is supported. Longitude/latitude geolocation might be added in the future.
