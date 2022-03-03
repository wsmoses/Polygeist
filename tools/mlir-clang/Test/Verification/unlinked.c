// RUN: mlir-clang %s --function=kernel_correlation --raise-scf-to-affine -S | FileCheck %s
// RUN: mlir-clang %s --function=kernel_correlation --raise-scf-to-affine -S -memref-fullrank | FileCheck %s --check-prefix=FULLRANK

#define DATA_TYPE double

#define N 10

#define match(b1, b2) (((b1)+(b2)) == 3 ? 1 : 0)
#define max_score(s1, s2) ((s1 >= s2) ? s1 : s2)

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_correlation(int table[N][N]) {
 for (int i = 9; i >= 0; i--) {
  for (int j=0; j<10; j++) {
      table[i][j] = i+j;
    }
  }
}

// CHECK:   func @kernel_correlation(%arg0: memref<?x10xi32>)
// CHECK-DAG:     %c9_i32 = arith.constant 9 : i32
// CHECK-DAG:     %c-1_i32 = arith.constant -1 : i32
// CHECK-NEXT:     affine.for %arg1 = 0 to 10 {
// CHECK-NEXT:       %0 = arith.index_cast %arg1 : index to i32
// CHECK-NEXT:       %1 = arith.muli %0, %c-1_i32 : i32
// CHECK-NEXT:       %2 = arith.addi %1, %c9_i32 : i32
// CHECK-NEXT:       affine.for %arg2 = 0 to 10 {
// CHECK-NEXT:         %3 = arith.index_cast %arg2 : index to i32
// CHECK-NEXT:         %4 = arith.addi %2, %3 : i32
// CHECK-NEXT:         affine.store %4, %arg0[-%arg1 + 9, %arg2] : memref<?x10xi32>
// CHECK-NEXT:       }
// CHECK-NEXT:     }
// CHECK-NEXT:     return
// CHECK-NEXT:   }

// FULLRANK:   func @kernel_correlation(%{{.*}}: memref<10x10xi32>)
