
add_compile_definitions(
        $<$<CONFIG:DEBUG>:TRYINLINE=>
        $<$<CONFIG:RELEASE>:TRYINLINE=inline>
)
