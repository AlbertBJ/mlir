add_subdirectory(lib)

set(LLVM_LINK_COMPONENTS
  Core
  Support
  )

set(LLVM_OPTIONAL_SOURCES Conversion.cpp Example.cpp)

add_llvm_example(linalg-conversion-1
  Conversion.cpp
  )

add_llvm_example(linalg-example-1
  Example.cpp
  )

target_link_libraries(linalg-example-1
  PRIVATE
    MLIRAnalysis
    MLIRDialect
    MLIREDSC
    MLIRIR
    MLIRLLVMIR
    MLIRParser
    MLIRPass
    MLIRTransforms
    Linalg1
    Linalg1DialectConstruction
    )

whole_archive_link(linalg-example-1
  MLIRStandardOps
  )

target_link_libraries(linalg-conversion-1
  PRIVATE
    MLIRAnalysis
    MLIRDialect
    MLIREDSC
    MLIRIR
    MLIRLLVMIR
    MLIRParser
    MLIRPass
    MLIRTransforms
    Linalg1
    Linalg1DialectConstruction
    )

whole_archive_link(linalg-conversion-1
  MLIRStandardOps
  )
