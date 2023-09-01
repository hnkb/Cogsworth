
    c_msvcrt typedef PROTO C :VARARG

    externdef _imp__memcpy:PTR c_msvcrt
    crt_memcpy equ <_imp__memcpy>
