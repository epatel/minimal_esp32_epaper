default: build

ifeq (, $(shell which pio))
$(info Please install PlatformIO CLI)
$(info See: https://docs.platformio.org/en/latest/core/installation.html#install-shell-commands)
$(error ..)
endif

clean:
	pio run --target clean

build:
	pio run

upload:
	pio run --target upload
