CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread  # Thêm thư viện pthread

# Danh sách các file nguồn và object
SRCS = main.c ring.c
OBJS = $(SRCS:.c=.o)

# Tên executable
TARGET = main

# Luật mặc định: build tất cả
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Biên dịch từng file .c thành .o
%.o: %.c ring.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean các file build
clean:
	rm -f $(OBJS) $(TARGET)
