# Watch

Simple file watcher.

This was a fun and educational project.  I started from the file watcher example in this sweet [libuv book] and built upon it.

## Dependencies

- [libuv]

## Building

```
gcc -Wall -o watch watch.c -luv
```

## Usage

    Property | Description
    ------------ | -------------
    -c | Command to run after a filesystem event is detected.

## Examples

```
./watch **/**.js -c npm run build
```

## Known Issues

Currently, the command MUST come after the files to be watched.

## License

[GPLv3](COPYING)

## Author

Benjamin Toll

[libuv]: https://github.com/libuv/libuv
[libuv book]: http://nikhilm.github.io/uvbook/filesystem.html#file-change-events

