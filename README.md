# CTIL

> Basic useful data structures in c

## install

```bash
git clone https://github.com/ephf/ctil.git
cd ctil
chmod o+x install.sh
sudo ./install.sh
```

Files can be removed without side effects.

```bash
cd ..
rm -rf ctil
```

## compile

```makefile
TARGET=<your_target>

$(TARGET): $(TARGET).o
	gcc -o $(TARGET) $(TARGET).o -lctil

$(TARGET).o: $(TARGET).c
	gcc -c -o $(TARGET).o $(TARGET).c
```