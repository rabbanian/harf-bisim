# Harf-bisim

Harf-bisim tries to implement a low-latency voice chat. with the help of Asio and OpenAL Soft.

## Build

- Harf-bisim uses CMake, if you're on Linux these commands should get you started:
 
```bash
$ git clone --recursive 'https://github.com/rabbanian/harf-bisim'
$ mkdir build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

### Build Options

Harf-bisim has two target `harf-bisim_client` and `harf-bisim_server`,
which are enabled and compiled by default. Use these options to disable them:

- WITH_CLIENT
- WITH_SERVER

e.g.:

```bash
$ cmake -DWITH_SERVER=OFF ..
```