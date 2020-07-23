default: clean build

ifeq (, $(shell which pio))
$(error "Please install PlatformIO CLI")
endif

clean:
	pio run --target clean

build:
	pio run

upload:
	pio run --target upload
