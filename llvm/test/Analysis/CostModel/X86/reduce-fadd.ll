; NOTE: Assertions have been autogenerated by utils/update_analyze_test_checks.py
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+sse2 | FileCheck %s --check-prefixes=SSE2
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+ssse3 | FileCheck %s --check-prefixes=SSSE3
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+sse4.1 | FileCheck %s --check-prefixes=SSE41
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+sse4.2 | FileCheck %s --check-prefixes=SSE42
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+avx | FileCheck %s --check-prefixes=AVX1
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+avx2 | FileCheck %s --check-prefixes=AVX2
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+avx512f | FileCheck %s --check-prefixes=AVX512
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+avx512f,+avx512bw | FileCheck %s --check-prefixes=AVX512
; RUN: opt < %s -cost-model -mtriple=x86_64-apple-darwin -analyze -mattr=+avx512f,+avx512dq | FileCheck %s --check-prefixes=AVX512

; CHECK: {{^}}
define void @reduce_f64(double %arg) {
; SSE2-LABEL: 'reduce_f64'
; SSE2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 2 for instruction: %V2 = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V4 = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 8 for instruction: %V8 = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 16 for instruction: %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; SSSE3-LABEL: 'reduce_f64'
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 2 for instruction: %V2 = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V4 = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 8 for instruction: %V8 = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 16 for instruction: %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; SSE41-LABEL: 'reduce_f64'
; SSE41-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 2 for instruction: %V2 = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V4 = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 8 for instruction: %V8 = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 16 for instruction: %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; SSE42-LABEL: 'reduce_f64'
; SSE42-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 2 for instruction: %V2 = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V4 = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 5 for instruction: %V8 = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 9 for instruction: %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; AVX1-LABEL: 'reduce_f64'
; AVX1-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 2 for instruction: %V2 = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V4 = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 5 for instruction: %V8 = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 9 for instruction: %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; AVX2-LABEL: 'reduce_f64'
; AVX2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 2 for instruction: %V2 = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V4 = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V8 = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 6 for instruction: %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; AVX512-LABEL: 'reduce_f64'
; AVX512-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 2 for instruction: %V2 = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V4 = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 6 for instruction: %V8 = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 7 for instruction: %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
  %V1  = call double @llvm.vector.reduce.fadd.v1f64(double %arg, <1 x double> undef)
  %V2  = call double @llvm.vector.reduce.fadd.v2f64(double %arg, <2 x double> undef)
  %V4  = call double @llvm.vector.reduce.fadd.v4f64(double %arg, <4 x double> undef)
  %V8  = call double @llvm.vector.reduce.fadd.v8f64(double %arg, <8 x double> undef)
  %V16 = call double @llvm.vector.reduce.fadd.v16f64(double %arg, <16 x double> undef)
  ret void
}

define void @reduce_f32(float %arg) {
; SSE2-LABEL: 'reduce_f32'
; SSE2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V2 = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V4 = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 6 for instruction: %V8 = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 10 for instruction: %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 18 for instruction: %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
; SSE2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; SSSE3-LABEL: 'reduce_f32'
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V2 = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V4 = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 6 for instruction: %V8 = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 10 for instruction: %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 18 for instruction: %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
; SSSE3-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; SSE41-LABEL: 'reduce_f32'
; SSE41-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V2 = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V4 = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 6 for instruction: %V8 = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 10 for instruction: %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 18 for instruction: %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
; SSE41-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; SSE42-LABEL: 'reduce_f32'
; SSE42-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V2 = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V4 = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 5 for instruction: %V8 = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 7 for instruction: %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 11 for instruction: %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
; SSE42-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; AVX1-LABEL: 'reduce_f32'
; AVX1-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V2 = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V4 = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V8 = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 6 for instruction: %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 10 for instruction: %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
; AVX1-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; AVX2-LABEL: 'reduce_f32'
; AVX2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V2 = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V4 = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V8 = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 5 for instruction: %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 7 for instruction: %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
; AVX2-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
; AVX512-LABEL: 'reduce_f32'
; AVX512-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: %V1 = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V2 = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 3 for instruction: %V4 = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 4 for instruction: %V8 = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 8 for instruction: %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 9 for instruction: %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
; AVX512-NEXT:  Cost Model: Found an estimated cost of 0 for instruction: ret void
;
  %V1  = call float @llvm.vector.reduce.fadd.v1f32(float %arg, <1 x float> undef)
  %V2  = call float @llvm.vector.reduce.fadd.v2f32(float %arg, <2 x float> undef)
  %V4  = call float @llvm.vector.reduce.fadd.v4f32(float %arg, <4 x float> undef)
  %V8  = call float @llvm.vector.reduce.fadd.v8f32(float %arg, <8 x float> undef)
  %V16 = call float @llvm.vector.reduce.fadd.v16f32(float %arg, <16 x float> undef)
  %V32 = call float @llvm.vector.reduce.fadd.v32f32(float %arg, <32 x float> undef)
  ret void
}

declare double @llvm.vector.reduce.fadd.v1f64(double, <1 x double>)
declare double @llvm.vector.reduce.fadd.v2f64(double, <2 x double>)
declare double @llvm.vector.reduce.fadd.v4f64(double, <4 x double>)
declare double @llvm.vector.reduce.fadd.v8f64(double, <8 x double>)
declare double @llvm.vector.reduce.fadd.v16f64(double, <16 x double>)

declare float @llvm.vector.reduce.fadd.v1f32(float, <1 x float>)
declare float @llvm.vector.reduce.fadd.v2f32(float, <2 x float>)
declare float @llvm.vector.reduce.fadd.v4f32(float, <4 x float>)
declare float @llvm.vector.reduce.fadd.v8f32(float, <8 x float>)
declare float @llvm.vector.reduce.fadd.v16f32(float, <16 x float>)
declare float @llvm.vector.reduce.fadd.v32f32(float, <32 x float>)
