# 🐕WatchDog

## Build, Debug, Run

```shell
sudo apt install libprotobuf-dev libgrpc++-dev libgrpc-dev protobuf-compiler-grpc
```

## Config

### Service Config

```json
{
    "name": "watchdog",
    "description": "WatchDog Service",
    "version": "0.0.1",
    "env": "dev",
    "host": "localhost",
    "port": 3000,
    "enabled": true,
    "log": {
        "level": "debug",
        "path": "logs/watchdog.log"
    },
    "watchdog": {
        "interval": 1000,
        "timeout": 5000
    }
}
```

## Watch

## Bite