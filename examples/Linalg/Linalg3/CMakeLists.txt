add_subdirectory(lib)

set(LLVM_LINK_COMPONENTS
  Core
  OrcJIT
  Support
  native
  )

set(LLVM_OPTIONAL_SOURCES
  Conversion.cpp
  Example.cpp
  Execution.cpp
  )

add_llvm_example(linalg-conversion-3
  Conversion.cpp
  )

add_llvm_example(linalg-example-3
  Example.cpp
  )

add_llvm_example(linalg-execution-3
  Execution.cpp
  )

target_link_libraries(linalg-example-3
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
    Linalg2
    Linalg3
    Linalg3DialectConstruction
    )

whole_archive_link(linalg-example-3
  MLIRStandardOps
  )

target_link_libraries(linalg-conversion-3
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
    Linalg2
    Linalg3
    Linalg3DialectConstruction
    )

whole_archive_link(linalg-conversion-3
  MLIRStandardOps
  )

target_link_libraries(linalg-execution-3
  PRIVATE
    MLIRAnalysis
    MLIRDialect
    MLIREDSC
    MLIRExecutionEngine
    MLIRIR
    MLIRLLVMIR
    MLIRParser
    MLIRPass
    MLIRSupport
    MLIRTargetLLVMIR
    MLIRTransforms
    Linalg1
    Linalg2
    Linalg3
    Linalg3DialectConstruction
    )

whole_archive_link(linalg-execution-3
  MLIRStandardOps
  )

