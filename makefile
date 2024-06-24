CC = gcc
CFLAGS = -Wall -Werror

Encoding_TARGET = Adidas_encoding
Decoding_TARGET = Adidas_decoding

Encoding_SRC = encodee.c
Decoding_SRC = decodee.c

all: $(Encoding_TARGET) $(Decoding_TARGET)

$(Encoding_TARGET): $(Encoding_SRC)
	$(CC) $(CFLAGS) $(Encoding_SRC) -o $(Encoding_TARGET)

$(Decoding_TARGET): $(Decoding_SRC)
	$(CC) $(CFLAGS) $(Decoding_SRC) -o $(Decoding_TARGET)

clean:
	rm -f $(Encoding_TARGET) $(Decoding_TARGET)
