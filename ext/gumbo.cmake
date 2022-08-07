add_library(gumbo STATIC
    gumbo-parser-0.10.1/src/attribute.c
    gumbo-parser-0.10.1/src/char_ref.c
    gumbo-parser-0.10.1/src/error.c
    gumbo-parser-0.10.1/src/parser.c
    gumbo-parser-0.10.1/src/string_buffer.c
    gumbo-parser-0.10.1/src/string_piece.c
    gumbo-parser-0.10.1/src/tag.c
    gumbo-parser-0.10.1/src/tokenizer.c
    gumbo-parser-0.10.1/src/utf8.c
    gumbo-parser-0.10.1/src/util.c
    gumbo-parser-0.10.1/src/vector.c
    gumbo-query/src/Document.cpp
    gumbo-query/src/Node.cpp
    gumbo-query/src/Object.cpp
    gumbo-query/src/Parser.cpp
    gumbo-query/src/QueryUtil.cpp
    gumbo-query/src/Selection.cpp
    gumbo-query/src/Selector.cpp
)
target_include_directories(gumbo PUBLIC
    gumbo-parser-0.10.1/src
    gumbo-query/src
)

set_target_properties(gumbo PROPERTIES POSITION_INDEPENDENT_CODE ON)