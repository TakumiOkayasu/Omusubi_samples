# Omusubi テスト用 Makefile

CXX = clang++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -I../include
LDFLAGS =

# テストファイル
TEST_SOURCES = test_span.cpp \
               test_string_view.cpp \
               test_fixed_string.cpp \
               test_fixed_buffer.cpp \
               test_vector3.cpp \
               test_all.cpp

# オブジェクトファイル
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# 実行ファイル
TARGET = test_runner

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TEST_OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
