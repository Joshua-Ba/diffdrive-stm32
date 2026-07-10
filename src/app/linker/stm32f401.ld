MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 256K
  RAM  (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
  .text :
  {
    KEEP(*(.isr_vector))   /* Vektortabelle */
    *(.text*)              /* Programmcode */
    *(.rodata*)            /* Konstanten */
  } >FLASH
  .data :
  {
    _sdata = .;        /* Start von .data im RAM (VMA) */
    *(.data*)
    _edata = .;        /* Ende von .data im RAM */
  } >RAM AT>FLASH

  _sidata = LOADADDR(.data);   /* Quelle im Flash (LMA) */

  .bss :
  {
    _sbss = .;        /* Start von .bss */
    *(.bss*)
    *(COMMON)
    _ebss = .;        /* Ende von .bss */
  } >RAM
}

_estack = ORIGIN(RAM) + LENGTH(RAM);
