# Use latest Fedora image
FROM fedora:latest

# Set working directory
WORKDIR /app

# Install gcc compiler
RUN dnf update -y && dnf install -y gcc

# Final image should not contain build tools
# Optional (replace with your desired entrypoint)
CMD ["/bin/bash"]
