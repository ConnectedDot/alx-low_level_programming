#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

// Print the ELF header information
void print_header(Elf64_Ehdr *header)
{
    printf("Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x ", header->e_ident[i]);
    printf("\n");
    printf("Class:   %s\n", header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" :
                            header->e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "unknown");
    printf("Data:    %s\n", header->e_ident[EI_DATA] == ELFDATA2LSB ? "little-endian" :
                            header->e_ident[EI_DATA] == ELFDATA2MSB ? "big-endian" : "unknown");
    printf("Version: %d\n", header->e_ident[EI_VERSION]);
    printf("OS/ABI:  %d\n", header->e_ident[EI_OSABI]);
    printf("ABI Ver: %d\n", header->e_ident[EI_ABIVERSION]);
    printf("Type:    %d\n", header->e_type);
    printf("Entry:   %lx\n", header->e_entry);
}

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        exit(98);
    }

    // Open the ELF file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(98);
    }

    // Read the ELF header
    Elf64_Ehdr header;
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        fprintf(stderr, "Error reading header from %s\n", argv[1]);
        close(fd);
        exit(98);
    }

    // Check that the file is actually an ELF file
    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "%s is not an ELF file\n", argv[1]);
        close(fd);
        exit(98);
    }

    // Print the ELF header information
    print_header(&header);

    // Clean up and exit
    close(fd);
    return (0);
}
