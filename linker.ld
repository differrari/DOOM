ENTRY(main)

SECTIONS {
    . = 0x1000;

    .text : {
        *(.text .text.*)
    }

    .bss : {
        *(.bss .bss.* COMMON)
    }

    .rodata : {
        *(.rodata .rodata.*)
    }

    .data : {
        *(.data .data.*)
    }

    /DISCARD/ : {
        *(.comment .note .eh_frame)
    }
}
