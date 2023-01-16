# Optimizations
- [IndexBuffer.h::IndexBuffer(const unsigned int* data, ...) Index buffers currently use 32bit unsigned int's. You can use 16bit unsigned short or char for better memory usage.
