CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

APP = monitor

SOURCES = src/main.cpp \
          src/driver_interface.cpp

all: $(APP) process_monitor process_watchdog device_monitor system_monitor driver

$(APP):
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(APP)

process_monitor:
	$(CXX) $(CXXFLAGS) src/process_monitor.cpp -o process_monitor

process_watchdog:
	$(CXX) $(CXXFLAGS) src/process_watchdog.cpp -o process_watchdog

device_monitor:
	$(CXX) $(CXXFLAGS) src/device_monitor.cpp -o device_monitor

system_monitor:
	$(CXX) $(CXXFLAGS) src/system_monitor.cpp -o system_monitor

driver:
	$(MAKE) -C driver

clean:
	rm -f $(APP) process_monitor process_watchdog device_monitor system_monitor
	$(MAKE) -C driver clean

.PHONY: all clean driver
