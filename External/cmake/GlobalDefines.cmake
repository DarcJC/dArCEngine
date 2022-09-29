
add_compile_definitions(
        $<$<CONFIG:DEBUG>:TRYINLINE=>
        $<$<CONFIG:RELEASE>:TRYINLINE=inline>
)

add_compile_definitions(
        $<$<CONFIG:DEBUG>:ENABLE_VALIDATION_LAYER=>
)

