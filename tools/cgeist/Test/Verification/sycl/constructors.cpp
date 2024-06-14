// RUN: clang++ -fsycl -fsycl-device-only -O0 -w -emit-mlir %s -o - -fpreview-breaking-changes | FileCheck %s --check-prefixes=CHECK
// RUN: clang++ -fsycl -fsycl-device-only -O0 -w -S -emit-llvm -fsycl-targets=spir64-unknown-unknown-syclmlir %s -o - -fpreview-breaking-changes | FileCheck %s --check-prefixes=CHECK-LLVM

#include <sycl/aliases.hpp>
#include <sycl/sycl.hpp>

// CHECK-DAG: !sycl_array_1_ = !sycl.array<[1], (memref<1xi64, 4>)>
// CHECK-DAG: !sycl_array_2_ = !sycl.array<[2], (memref<2xi64, 4>)>
// CHECK-DAG: !sycl_id_1_ = !sycl.id<[1], (!sycl_array_1_)>
// CHECK-DAG: !sycl_id_2_ = !sycl.id<[2], (!sycl_array_2_)>
// CHECK-DAG: !sycl_range_1_ = !sycl.range<[1], (!sycl_array_1_)>
// CHECK-DAG: !sycl_range_2_ = !sycl.range<[2], (!sycl_array_2_)>
// CHECK-DAG: !sycl_accessor_impl_device_1_ = !sycl.accessor_impl_device<[1], (!sycl_id_1_, !sycl_range_1_, !sycl_range_1_)>
// CHECK-DAG: !sycl_accessor_1_i32_w_dev = !sycl.accessor<[1, i32, write, device], (!sycl_accessor_impl_device_1_, !llvm.struct<(memref<?xi32, 1>)>)>
// CHECK-DAG: ![[ITEM_BASE:.*]] = !sycl.item_base<[2, true], (!sycl_range_2_, !sycl_id_2_, !sycl_id_2_)>
// CHECK-DAG: ![[ITEM:.*]] = !sycl.item<[2, true], (![[ITEM_BASE]])>

// Check globals referenced in device functions are created in the GPU module
// CHECK: gpu.module @device_functions {
// CHECK-DAG: memref.global constant @__spirv_BuiltInSubgroupLocalInvocationId : memref<i32, 1> {alignment = 4 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInSubgroupId : memref<i32, 1> {alignment = 4 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInNumSubgroups : memref<i32, 1> {alignment = 4 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInSubgroupMaxSize : memref<i32, 1> {alignment = 4 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInSubgroupSize : memref<i32, 1> {alignment = 4 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInLocalInvocationId : memref<vector<3xi64>, 1> {alignment = 32 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInWorkgroupId : memref<vector<3xi64>, 1> {alignment = 32 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInWorkgroupSize : memref<vector<3xi64>, 1> {alignment = 32 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInNumWorkgroups : memref<vector<3xi64>, 1> {alignment = 32 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInGlobalOffset : memref<vector<3xi64>, 1> {alignment = 32 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInGlobalSize : memref<vector<3xi64>, 1> {alignment = 32 : i64}
// CHECK-DAG: memref.global constant @__spirv_BuiltInGlobalInvocationId : memref<vector<3xi64>, 1> {alignment = 32 : i64}

// CHECK-LLVM-DAG: @__spirv_BuiltInSubgroupLocalInvocationId = external addrspace(1) constant i32, align 4
// CHECK-LLVM-DAG: @__spirv_BuiltInSubgroupId = external addrspace(1) constant i32, align 4
// CHECK-LLVM-DAG: @__spirv_BuiltInNumSubgroups = external addrspace(1) constant i32, align 4
// CHECK-LLVM-DAG: @__spirv_BuiltInSubgroupMaxSize = external addrspace(1) constant i32, align 4
// CHECK-LLVM-DAG: @__spirv_BuiltInSubgroupSize = external addrspace(1) constant i32, align 4
// CHECK-LLVM-DAG: @__spirv_BuiltInLocalInvocationId = external addrspace(1) constant <3 x i64>, align 32
// CHECK-LLVM-DAG: @__spirv_BuiltInWorkgroupId = external addrspace(1) constant <3 x i64>, align 32
// CHECK-LLVM-DAG: @__spirv_BuiltInWorkgroupSize = external addrspace(1) constant <3 x i64>, align 32
// CHECK-LLVM-DAG: @__spirv_BuiltInNumWorkgroups = external addrspace(1) constant <3 x i64>, align 32
// CHECK-LLVM-DAG: @__spirv_BuiltInGlobalOffset = external addrspace(1) constant <3 x i64>, align 32
// CHECK-LLVM-DAG: @__spirv_BuiltInGlobalSize = external addrspace(1) constant <3 x i64>, align 32
// CHECK-LLVM-DAG: @__spirv_BuiltInGlobalInvocationId = external addrspace(1) constant <3 x i64>, align 32

// Ensure the spirv functions that reference these globals are not filtered out
// CHECK-DAG: func.func @_Z28__spirv_GlobalInvocationId_xv()
// CHECK-DAG: func.func @_Z28__spirv_GlobalInvocationId_yv()
// CHECK-DAG: func.func @_Z28__spirv_GlobalInvocationId_zv()
// CHECK-DAG: func.func @_Z20__spirv_GlobalSize_xv()
// CHECK-DAG: func.func @_Z20__spirv_GlobalSize_yv()
// CHECK-DAG: func.func @_Z20__spirv_GlobalSize_zv()
// CHECK-DAG: func.func @_Z22__spirv_GlobalOffset_xv()
// CHECK-DAG: func.func @_Z22__spirv_GlobalOffset_yv()
// CHECK-DAG: func.func @_Z22__spirv_GlobalOffset_zv()
// CHECK-DAG: func.func @_Z23__spirv_NumWorkgroups_xv()
// CHECK-DAG: func.func @_Z23__spirv_NumWorkgroups_yv()
// CHECK-DAG: func.func @_Z23__spirv_NumWorkgroups_zv()
// CHECK-DAG: func.func @_Z23__spirv_WorkgroupSize_xv()
// CHECK-DAG: func.func @_Z23__spirv_WorkgroupSize_yv()
// CHECK-DAG: func.func @_Z23__spirv_WorkgroupSize_zv()
// CHECK-DAG: func.func @_Z21__spirv_WorkgroupId_xv()
// CHECK-DAG: func.func @_Z21__spirv_WorkgroupId_yv()
// CHECK-DAG: func.func @_Z21__spirv_WorkgroupId_zv()
// CHECK-DAG: func.func @_Z27__spirv_LocalInvocationId_xv()
// CHECK-DAG: func.func @_Z27__spirv_LocalInvocationId_yv()
// CHECK-DAG: func.func @_Z27__spirv_LocalInvocationId_zv()
// CHECK-DAG: func.func @_Z18__spirv_SubgroupIdv()
// CHECK-DAG: func.func @_Z33__spirv_SubgroupLocalInvocationIdv()
// CHECK-DAG: func.func @_Z23__spirv_SubgroupMaxSizev()
// CHECK-DAG: func.func @_Z20__spirv_NumSubgroupsv()

// Ensure the constructors are NOT filtered out, and sycl.cast is generated for cast from sycl.id or sycl.range to sycl.array.
// CHECK:           func.func @cons_0(%[[VAL_151:.*]]: memref<?x!sycl_id_1_> {llvm.align = 8 : i64, llvm.byval = !sycl_id_1_, llvm.noundef}, %[[VAL_152:.*]]: memref<?x!sycl_range_1_> {llvm.align = 8 : i64, llvm.byval = !sycl_range_1_, llvm.noundef})
// CHECK-SAME: attributes {[[SPIR_FUNCCC:llvm.cconv = #llvm.cconv<spir_funccc>]], [[LINKEXTERNAL:llvm.linkage = #llvm.linkage<external>]], {{.*}}} {
// CHECK:             %[[VAL_153:.*]] = arith.constant 8 : i64
// CHECK:             %[[VAL_154:.*]] = memref.alloca() : memref<1x!sycl_range_1_>
// CHECK:             %[[VAL_155:.*]] = memref.cast %[[VAL_154]] : memref<1x!sycl_range_1_> to memref<?x!sycl_range_1_>
// CHECK:             %[[VAL_156:.*]] = memref.alloca() : memref<1x!sycl_id_1_>
// CHECK:             %[[VAL_157:.*]] = memref.cast %[[VAL_156]] : memref<1x!sycl_id_1_> to memref<?x!sycl_id_1_>
// CHECK:             %[[VAL_158:.*]] = memref.memory_space_cast %[[VAL_157]] : memref<?x!sycl_id_1_> to memref<?x!sycl_id_1_, 4>
// CHECK:             %[[VAL_160:.*]] = sycl.id.constructor(%[[VAL_151]]) : (memref<?x!sycl_id_1_>) -> memref<?x!sycl_id_1_, 4>
// CHECK:             %[[VAL_161:.*]] = "polygeist.memref2pointer"(%[[VAL_158]]) : (memref<?x!sycl_id_1_, 4>) -> !llvm.ptr<4>
// CHECK:             %[[VAL_162:.*]] = "polygeist.memref2pointer"(%[[VAL_160]]) : (memref<?x!sycl_id_1_, 4>) -> !llvm.ptr<4>
// CHECK:             "llvm.intr.memcpy"(%[[VAL_161]], %[[VAL_162]], %[[VAL_153]]) <{isVolatile = false}> : (!llvm.ptr<4>, !llvm.ptr<4>, i64) -> ()
// CHECK:             %[[VAL_163:.*]] = memref.memory_space_cast %[[VAL_155]] : memref<?x!sycl_range_1_> to memref<?x!sycl_range_1_, 4>
// CHECK:             %[[VAL_165:.*]] = sycl.range.constructor(%[[VAL_152]]) : (memref<?x!sycl_range_1_>) -> memref<?x!sycl_range_1_, 4>
// CHECK:             %[[VAL_166:.*]] = "polygeist.memref2pointer"(%[[VAL_163]]) : (memref<?x!sycl_range_1_, 4>) -> !llvm.ptr<4>
// CHECK:             %[[VAL_167:.*]] = "polygeist.memref2pointer"(%[[VAL_165]]) : (memref<?x!sycl_range_1_, 4>) -> !llvm.ptr<4>
// CHECK:             "llvm.intr.memcpy"(%[[VAL_166]], %[[VAL_167]], %[[VAL_153]]) <{isVolatile = false}> : (!llvm.ptr<4>, !llvm.ptr<4>, i64) -> ()
// CHECK:             return

// CHECK-LLVM: define spir_func void @cons_0(ptr noundef byval([[ID_TYPE:%"class.sycl::_V1::id.1"]]) align 8 [[ARG0:%.*]], 
// CHECK-LLVM-SAME:                          ptr noundef byval([[RANGE_TYPE:%"class.sycl::_V1::range.1"]]) align 8 [[ARG1:%.*]]) #[[FUNCATTRS:[0-9]+]]
// CHECK-LLVM-NEXT:   [[RANGE:%.*]] = alloca [[RANGE_TYPE]], i64 1, align 8
// CHECK-LLVM-NEXT:   [[ID:%.*]] = alloca [[ID_TYPE]], i64 1, align 8
// CHECK-LLVM-NEXT:   [[ID_AS:%.*]] = addrspacecast ptr [[ID]] to ptr addrspace(4)
// CHECK-LLVM-NEXT:   [[TMP:%.*]] = alloca [[ID_TYPE]], align 8
// CHECK-LLVM-NEXT:   [[TMP_AS:%.*]] = addrspacecast ptr [[TMP]] to ptr addrspace(4)
// CHECK-LLVM-NEXT:   call void @llvm.memcpy.p4.p0.i64(ptr addrspace(4) [[TMP_AS]], ptr [[ARG0]], i64 8, i1 false)
// CHECK-LLVM-NEXT:   call void @llvm.memcpy.p4.p4.i64(ptr addrspace(4) [[ID_AS]], ptr addrspace(4) [[TMP_AS]], i64 8, i1 false)
// CHECK-LLVM-NEXT:   [[RANGE_AS:%.*]] = addrspacecast ptr [[RANGE]] to ptr addrspace(4)
// CHECK-LLVM-NEXT:   [[TMP:%.*]] = alloca [[RANGE_TYPE]], align 8
// CHECK-LLVM-NEXT:   [[TMP_AS:%.*]] = addrspacecast ptr [[TMP]] to ptr addrspace(4)
// CHECK-LLVM-NEXT:   call void @llvm.memcpy.p4.p0.i64(ptr addrspace(4) [[TMP_AS]], ptr [[ARG1]], i64 8, i1 false)
// CHECK-LLVM-NEXT:   call void @llvm.memcpy.p4.p4.i64(ptr addrspace(4) [[RANGE_AS]], ptr addrspace(4) [[TMP_AS]], i64 8, i1 false)
// CHECK-LLVM-NEXT:   ret void

extern "C" SYCL_EXTERNAL void cons_0(sycl::id<1> i, sycl::range<1> r) {
  auto id = sycl::id<1>{i};
  auto range = sycl::range<1>{r};
}

// CHECK-LABEL: func.func @cons_1()
// CHECK-SAME: attributes {[[SPIR_FUNCCC]], [[LINKEXTERNAL:llvm.linkage = #llvm.linkage<external>]], {{.*}}} {
// CHECK:             %[[VAL_176:.*]] = arith.constant 16 : i64
// CHECK:             %[[VAL_177:.*]] = arith.constant 0 : i8
// CHECK:             %[[VAL_178:.*]] = memref.alloca() : memref<1x!sycl_id_2_>
// CHECK:             %[[VAL_179:.*]] = memref.cast %[[VAL_178]] : memref<1x!sycl_id_2_> to memref<?x!sycl_id_2_>
// CHECK:             %[[VAL_180:.*]] = "polygeist.memref2pointer"(%[[VAL_178]]) : (memref<1x!sycl_id_2_>) -> !llvm.ptr
// CHECK:             %[[VAL_181:.*]] = "polygeist.typeSize"() <{source = !sycl_id_2_}> : () -> index
// CHECK:             %[[VAL_182:.*]] = arith.index_cast %[[VAL_181]] : index to i64
// CHECK:             "llvm.intr.memset"(%[[VAL_180]], %[[VAL_177]], %[[VAL_182]]) <{isVolatile = false}> : (!llvm.ptr, i8, i64) -> ()
// CHECK:             %[[VAL_183:.*]] = memref.memory_space_cast %[[VAL_179]] : memref<?x!sycl_id_2_> to memref<?x!sycl_id_2_, 4>
// CHECK:             %[[VAL_184:.*]] = sycl.id.constructor() : () -> memref<?x!sycl_id_2_, 4>
// CHECK:             %[[VAL_185:.*]] = "polygeist.memref2pointer"(%[[VAL_183]]) : (memref<?x!sycl_id_2_, 4>) -> !llvm.ptr<4>
// CHECK:             %[[VAL_186:.*]] = "polygeist.memref2pointer"(%[[VAL_184]]) : (memref<?x!sycl_id_2_, 4>) -> !llvm.ptr<4>
// CHECK:             "llvm.intr.memcpy"(%[[VAL_185]], %[[VAL_186]], %[[VAL_176]]) <{isVolatile = false}> : (!llvm.ptr<4>, !llvm.ptr<4>, i64) -> ()
// CHECK:             return

// CHECK-LLVM-LABEL: define spir_func void @cons_1()
// CHECK-LLVM-SAME:  #[[FUNCATTRS]]
// CHECK-LLVM: [[ID1:%.*]] = alloca [[ID_TYPE:%"class.sycl::_V1::id.2"]]
// CHECK-LLVM: call void @llvm.memset.p0.i64(ptr [[ID1]], i8 0, i64 16, i1 false)
// CHECK-LLVM: [[ID1_AS:%.*]] = addrspacecast ptr [[ID1]] to ptr addrspace(4)
// CHECK-LLVM: [[ID2:%.*]] = alloca %"class.sycl::_V1::id.2", align 8
// CHECK-LLVM: [[ID2_AS:%.*]] = addrspacecast ptr [[ID2]] to ptr addrspace(4)
// CHECK-LLVM: call void @llvm.memset.p4.i64(ptr addrspace(4) [[ID2_AS]], i8 0, i64 16, i1 false)
// CHECK-LLVM: call void @llvm.memcpy.p4.p4.i64(ptr addrspace(4) [[ID1_AS]], ptr addrspace(4) [[ID2_AS]], i64 16, i1 false)

extern "C" SYCL_EXTERNAL void cons_1() {
  auto id = sycl::id<2>{};
}

// CHECK-LABEL: func.func @cons_2(%arg0: i64 {llvm.noundef}, %arg1: i64 {llvm.noundef})
// CHECK-SAME: attributes {[[SPIR_FUNCCC]], [[LINKEXTERNAL]], {{.*}}}
// CHECK-NEXT: %alloca = memref.alloca() : memref<1x!sycl_id_2_>
// CHECK-NEXT: %cast = memref.cast %alloca : memref<1x!sycl_id_2_> to memref<?x!sycl_id_2_>
// CHECK-NEXT: %memspacecast = memref.memory_space_cast %cast : memref<?x!sycl_id_2_> to memref<?x!sycl_id_2_, 4>
// CHECK-NEXT: sycl.constructor @id(%memspacecast, %arg0, %arg1) {MangledFunctionName = @_ZN4sycl3_V12idILi2EEC1ILi2EEENSt9enable_ifIXeqT_Li2EEmE4typeEm} : (memref<?x!sycl_id_2_, 4>, i64, i64)

// CHECK-LLVM-LABEL: define spir_func void @cons_2(i64 noundef %0, i64 noundef %1)
// CHECK-LLVM-SAME:  #[[FUNCATTRS]]
// CHECK-LLVM: [[ID1:%.*]] = alloca [[ID_TYPE:%"class.sycl::_V1::id.2"]]
// CHECK-LLVM: [[ID1_AS:%.*]] = addrspacecast ptr [[ID1]] to ptr addrspace(4)
// CHECK-LLVM: call spir_func void @_ZN4sycl3_V12idILi2EEC1ILi2EEENSt9enable_ifIXeqT_Li2EEmE4typeEm(ptr addrspace(4) noundef align 8 dereferenceable_or_null(16) [[ID1_AS]], i64 noundef %0, i64 noundef %1)

extern "C" SYCL_EXTERNAL void cons_2(size_t a, size_t b) {
  auto id = sycl::id<2>{a, b};
}

// CHECK-LABEL: func.func @cons_3(
// CHECK-SAME:    %[[VAL_198:.*]]: memref<?x!sycl_item_2_>
// CHECK:             %[[VAL_199:.*]] = arith.constant 16 : i64
// CHECK:             %[[VAL_200:.*]] = memref.alloca() : memref<1x!sycl_id_2_>
// CHECK:             %[[VAL_201:.*]] = memref.cast %[[VAL_200]] : memref<1x!sycl_id_2_> to memref<?x!sycl_id_2_>
// CHECK:             %[[VAL_202:.*]] = memref.memory_space_cast %[[VAL_201]] : memref<?x!sycl_id_2_> to memref<?x!sycl_id_2_, 4>
// CHECK:             %[[VAL_204:.*]] = sycl.id.constructor(%[[VAL_198]]) : (memref<?x!sycl_item_2_>) -> memref<?x!sycl_id_2_, 4>
// CHECK:             %[[VAL_205:.*]] = "polygeist.memref2pointer"(%[[VAL_202]]) : (memref<?x!sycl_id_2_, 4>) -> !llvm.ptr<4>
// CHECK:             %[[VAL_206:.*]] = "polygeist.memref2pointer"(%[[VAL_204]]) : (memref<?x!sycl_id_2_, 4>) -> !llvm.ptr<4>
// CHECK:             "llvm.intr.memcpy"(%[[VAL_205]], %[[VAL_206]], %[[VAL_199]]) <{isVolatile = false}> : (!llvm.ptr<4>, !llvm.ptr<4>, i64) -> ()
// CHECK:             return

// CHECK-LLVM: define spir_func void @cons_3(ptr noundef byval([[ITEM_TYPE:%"class.sycl::_V1::item.2.true"]]) align 8 [[ARG0:%.*]]) #[[FUNCATTRS]]
// CHECK-LLVM-DAG: [[ID:%.*]] = alloca [[ID_TYPE:%"class.sycl::_V1::id.2"]]  
// CHECK-LLVM: [[ID_AS:%.*]] = addrspacecast ptr [[ID]] to ptr addrspace(4)
// CHECK-LLVM: [[ID2:%.*]] = alloca %"class.sycl::_V1::id.2", align 8
// CHECK-LLVM: [[ID2_AS:%.*]] = addrspacecast ptr [[ID2]] to ptr addrspace(4)
// CHECK-LLVM: [[GEP0:%.*]] = getelementptr inbounds %"class.sycl::_V1::item.2.true", ptr [[ARG0]], i32 0, i32 0, i32 1, i32 0, i32 0, i32 0
// CHECK-LLVM: [[D0:%.*]] = load i64, ptr [[GEP0]], align 8
// CHECK-LLVM: [[GEP1:%.*]] = getelementptr inbounds %"class.sycl::_V1::item.2.true", ptr [[ARG0]], i32 0, i32 0, i32 1, i32 0, i32 0, i32 1
// CHECK-LLVM: [[V1:%.*]] = load i64, ptr [[GEP1]], align 8
// CHECK-LLVM: [[GEP2:%.*]] = getelementptr inbounds %"class.sycl::_V1::id.2", ptr [[ID2]], i32 0, i32 0, i32 0, i32 0
// CHECK-LLVM: store i64 [[D0]], ptr [[GEP2]], align 8
// CHECK-LLVM: [[GEP3:%.*]] = getelementptr inbounds %"class.sycl::_V1::id.2", ptr [[ID2]], i32 0, i32 0, i32 0, i32 1
// CHECK-LLVM: store i64 [[V1]], ptr [[GEP3]], align 8
// CHECK-LLVM: call void @llvm.memcpy.p4.p4.i64(ptr addrspace(4) [[ID_AS]], ptr addrspace(4) [[ID2_AS]], i64 16, i1 false)

extern "C" SYCL_EXTERNAL void cons_3(sycl::item<2, true> val) {
  auto id = sycl::id<2>{val};
}

// CHECK-LABEL: func.func @cons_4(%arg0: memref<?x!sycl_id_2_> {llvm.align = 8 : i64, llvm.byval = !sycl_id_2_, llvm.noundef})
// CHECK-SAME: attributes {[[SPIR_FUNCCC]], [[LINKEXTERNAL]], {{.*}}}
// CHECK-NEXT: %[[SIZE:.*]] = arith.constant 16 : i64
// CHECK-NEXT: %alloca = memref.alloca() : memref<1x!sycl_id_2_>
// CHECK-NEXT: %cast = memref.cast %alloca : memref<1x!sycl_id_2_> to memref<?x!sycl_id_2_>
// CHECK-NEXT: %memspacecast = memref.memory_space_cast %cast : memref<?x!sycl_id_2_> to memref<?x!sycl_id_2_, 4>
// CHECK-NEXT: %[[VAL_212:.*]] = sycl.id.constructor(%arg0) : (memref<?x!sycl_id_2_>) -> memref<?x!sycl_id_2_, 4>
// CHECK-NEXT: %[[VAL_213:.*]] = "polygeist.memref2pointer"(%memspacecast) : (memref<?x!sycl_id_2_, 4>) -> !llvm.ptr<4>
// CHECK-NEXT: %[[VAL_214:.*]] = "polygeist.memref2pointer"(%[[VAL_212]]) : (memref<?x!sycl_id_2_, 4>) -> !llvm.ptr<4>
// CHECK-NEXT: "llvm.intr.memcpy"(%[[VAL_213]], %[[VAL_214]], %[[SIZE]]) <{isVolatile = false}> : (!llvm.ptr<4>, !llvm.ptr<4>, i64) -> ()

// CHECK-LLVM: define spir_func void @cons_4(ptr noundef byval([[ID_TYPE:%"class.sycl::_V1::id.2"]]) align 8 [[ARG0:%.*]]) #[[FUNCATTRS]]
// CHECK-LLVM-DAG: [[ID:%.*]] = alloca [[ID_TYPE]]
// CHECK-LLVM: [[ID1_AS:%.*]] = addrspacecast ptr [[ID]] to ptr addrspace(4)
// CHECK-LLVM: [[TMP:%.*]] = alloca [[ID_TYPE]]
// CHECK-LLVM: [[TMP_AS:%.*]] = addrspacecast ptr [[TMP]] to ptr addrspace(4)
// CHECK-LLVM: call void @llvm.memcpy.p4.p0.i64(ptr addrspace(4) [[TMP_AS]], ptr [[ARG0]], i64 16, i1 false)
// CHECK-LLVM: call void @llvm.memcpy.p4.p4.i64(ptr addrspace(4) [[ID1_AS]], ptr addrspace(4) [[TMP_AS]], i64 16, i1 false) 

extern "C" SYCL_EXTERNAL void cons_4(sycl::id<2> val) {
  auto id = sycl::id<2>{val};
}

// CHECK-LABEL: func.func @_ZN4sycl3_V18accessorIiLi1ELNS0_6access4modeE1025ELNS2_6targetE2014ELNS2_11placeholderE0ENS0_3ext6oneapi22accessor_property_listIJEEEEC1Ev(
// CHECK-SAME: {{.*}}) attributes {[[SPIR_FUNCCC]], [[LINKONCE:llvm.linkage = #llvm.linkage<linkonce_odr>]], {{.*}}}
// CHECK: [[I:%.*]] = "polygeist.subindex"(%arg0, %c0) : (memref<?x!sycl_accessor_1_i32_w_dev, 4>, index) -> memref<?x!sycl_accessor_impl_device_1_, 4>
// CHECK: sycl.constructor @AccessorImplDevice([[I]], {{%.*}}, {{%.*}}, {{%.*}}) {MangledFunctionName = @_ZN4sycl3_V16detail18AccessorImplDeviceILi1EEC1ENS0_2idILi1EEENS0_5rangeILi1EEES7_} : (memref<?x!sycl_accessor_impl_device_1_, 4>, memref<?x!sycl_id_1_>, memref<?x!sycl_range_1_>, memref<?x!sycl_range_1_>)

// CHECK-LLVM-LABEL: define spir_func void @cons_5()
// CHECK-LLVM-SAME:  #[[FUNCATTRS]]
// CHECK-LLVM: [[ACCESSOR:%.*]] = alloca %"class.sycl::_V1::accessor.1", i64 1, align 8
// CHECK-LLVM: [[ACAST:%.*]] = addrspacecast ptr [[ACCESSOR]] to ptr addrspace(4)
// CHECK-LLVM: call spir_func void @_ZN4sycl3_V18accessorIiLi1ELNS0_6access4modeE1025ELNS2_6targetE2014ELNS2_11placeholderE0ENS0_3ext6oneapi22accessor_property_listIJEEEEC1Ev(ptr addrspace(4) noundef align 8 dereferenceable_or_null(32) [[ACAST]])

extern "C" SYCL_EXTERNAL void cons_5() {
  auto accessor = sycl::accessor<sycl::cl_int, 1, sycl::access::mode::write>{};
}

// CHECK-LABEL: func.func @cons_6(
// CHECK-SAME:                    %{{.*}}: i32
// CHECK:         sycl.constructor @vec({{.*}}, {{.*}}) {MangledFunctionName = @[[VEC_SPLAT_CTR:.*]]} : (memref<?x!sycl_vec_i32_8_, 4>, memref<?xi32, 4>)
// CHECK:         func.func @[[VEC_SPLAT_CTR]](%{{.*}}: memref<?x!sycl_vec_i32_8_, 4> {{{.*}}}, %{{.*}}: memref<?xi32, 4> {{{.*}}}) attributes {[[SPIR_FUNCCC]], [[LINKONCE]], {{.*}}}
// CHECK:         vector.splat %{{.*}} : vector<8xi32>

// CHECK-LLVM-LABEL: define spir_func void @cons_6(
// CHECK-LLVM-SAME:                                i32 noundef %{{.*}}) #[[FUNCATTRS]]
// CHECK-LLVM:         call spir_func void @[[VEC_SPLAT_CTR:.*]](ptr addrspace(4) noundef align 32 dereferenceable_or_null(32) %{{.*}}, ptr addrspace(4) noundef align 4 dereferenceable(4) %{{.*}})
// CHECK-LLVM:       define linkonce_odr spir_func void @[[VEC_SPLAT_CTR]](ptr addrspace(4) noundef align 32 dereferenceable_or_null(32) %{{.*}}, ptr addrspace(4) noundef align 4 dereferenceable(4) %{{.*}}) #[[FUNCATTRS]] {
// CHECK-LLVM:         %[[VECINIT:.*]] = insertelement <8 x i32> undef, i32 %{{.*}}, i32 0
// CHECK-LLVM:         %{{.*}} = shufflevector <8 x i32> %[[VECINIT]], <8 x i32> undef, <8 x i32> zeroinitializer

extern "C" SYCL_EXTERNAL void cons_6(int Arg) {
  auto vec = sycl::vec<sycl::cl_int, 8>{Arg};
}

// CHECK-LABEL: func.func @cons_7(
// CHECK-SAME:                    %[[ARG0:.*]]: f32 {{{.*}}}, %[[ARG1:.*]]: f32 {{{.*}}}, %[[ARG2:.*]]: f32 {{{.*}}}, %[[ARG3:.*]]: f32 {{{.*}}})
// CHECK:         sycl.constructor @vec(%{{.*}}, %[[ARG0]], %[[ARG1]], %[[ARG2]], %[[ARG3]]) {MangledFunctionName = @[[VEC_INITLIST_CTR:.*]]} : (memref<?x!sycl_vec_f32_4_, 4>, f32, f32, f32, f32)
// CHECK:       func.func @[[VEC_INITLIST_CTR]](%{{.*}}: memref<?x!sycl_vec_f32_4_, 4> {{{.*}}}, %{{.*}}: f32 {{{.*}}}, %{{.*}}: f32 {{{.*}}}, %{{.*}}: f32 {{{.*}}}, %{{.*}}: f32 {{{.*}}}) attributes {[[SPIR_FUNCCC]], [[LINKONCE]], {{.*}}}

// CHECK-LLVM-LABEL: define spir_func void @cons_7(
// CHECK-LLVM-SAME:                                float noundef %[[ARG0:.*]], float noundef %[[ARG1:.*]], float noundef %[[ARG2:.*]], float noundef %[[ARG3:.*]]) #[[FUNCATTRS]]
// CHECK-LLVM:         call spir_func void @[[VEC_INITLIST_CTR:.*]](ptr addrspace(4) noundef align 16 dereferenceable_or_null(16) %{{.*}}, float noundef %[[ARG0]], float noundef %[[ARG1]], float noundef %[[ARG2]], float noundef %[[ARG3]])
// CHECK-LLVM:       define linkonce_odr spir_func void @[[VEC_INITLIST_CTR]](ptr addrspace(4) noundef align 16 {{.*}}, float noundef {{.*}}, float noundef {{.*}}, float noundef {{.*}}, float noundef {{.*}}) #[[FUNCATTRS]]
extern "C" SYCL_EXTERNAL void cons_7(float A, float B, float C, float D) {
  auto vec = sycl::vec<sycl::cl_float, 4>{A, B, C, D};
}

// CHECK-LABEL: func.func @cons_8(
// CHECK-SAME:                    %[[ARG0:.*]]: memref<?x!sycl_vec_f64_16_, 4> {{{.*}}})
// CHECK:         sycl.constructor @vec(%{{.*}}, %[[ARG0]]) {MangledFunctionName = @[[VEC_COPY_CTR:.*]]} : (memref<?x!sycl_vec_f64_16_, 4>, memref<?x!sycl_vec_f64_16_, 4>)
// CHECK:       func.func @[[VEC_COPY_CTR]](%{{.*}}: memref<?x!sycl_vec_f64_16_, 4> {{{.*}}}, %{{.*}}: memref<?x!sycl_vec_f64_16_, 4> {{{.*}}}) attributes {[[SPIR_FUNCCC]], [[LINKONCE]], {{.*}}}

// CHECK-LLVM-LABEL:  define spir_func void @cons_8(
// CHECK-LLVM-SAME:                                 ptr addrspace(4) noundef align 64 dereferenceable(128) %[[ARG0:.*]]) #[[FUNCATTRS]] {
// CHECK-LLVM:          call spir_func void @_ZN4sycl3_V13vecIdLi16EEC1ERKS2_(ptr addrspace(4) noundef align 64 dereferenceable_or_null(128) %{{.*}}, ptr addrspace(4) noundef align 64 dereferenceable(128) %[[ARG0]])
// CHECK-LLVM:        define linkonce_odr spir_func void @_ZN4sycl3_V13vecIdLi16EEC1ERKS2_(ptr addrspace(4) noundef align 64 dereferenceable_or_null(128) %{{.*}}, ptr addrspace(4) noundef align 64 dereferenceable(128) %{{.*}}) #[[FUNCATTRS]] {
extern "C" SYCL_EXTERNAL void cons_8(const sycl::vec<sycl::cl_double, 16> &Other) {
  auto vec = sycl::vec<sycl::cl_double, 16>{Other};
}

// CHECK-LABEL: func.func @cons_9(
// CHECK-SAME:                    %[[ARG0:.*]]: vector<3xi8>
// CHECK:         sycl.constructor @vec(%{{.*}}, %[[ARG0]]) {MangledFunctionName = @[[VEC_NATIVE_CTR:.*]]} : (memref<?x!sycl_vec_i8_3_, 4>, vector<3xi8>)
// CHECK:       func.func @[[VEC_NATIVE_CTR]](%{{.*}}: memref<?x!sycl_vec_i8_3_, 4> {{{.*}}}, %{{.*}}: vector<3xi8> {{{.*}}}) attributes {[[SPIR_FUNCCC]], [[LINKONCE]], {{.*}}}

// CHECK-LLVM-LABEL:  define spir_func void @cons_9(
// CHECK-LLVM-SAME:                                 <3 x i8> noundef %[[ARG0:.*]]) #[[FUNCATTRS]] {
// CHECK-LLVM:          call spir_func void @[[VEC_NATIVE_CTR:.*]](ptr addrspace(4) noundef align 4 dereferenceable_or_null(4) %{{.*}}, <3 x i8> noundef %[[ARG0]])
// CHECK-LLVM:        define linkonce_odr spir_func void @[[VEC_NATIVE_CTR]](ptr addrspace(4) noundef align 4 dereferenceable_or_null(4) %{{.*}}, <3 x i8> noundef %{{.*}}) #[[FUNCATTRS]] {
extern "C" SYCL_EXTERNAL void cons_9(const sycl::vec<sycl::cl_char, 3>::vector_t Native) {
  auto vec = sycl::vec<sycl::cl_char, 3>{Native};
}

// CHECK-LABEL: func.func @cons_10(
// CHECK-SAME:                     %[[ARG0:.*]]: memref<?x!sycl_vec_i64_8_, 4> {{{.*}}}, %[[ARG1:.*]]: memref<?x!sycl_vec_i64_4_, 4> {{{.*}}}, %[[ARG2:.*]]: memref<?x!sycl_vec_i64_2_, 4> {{{.*}}}, %{{.*}}: i64 {{{.*}}}, %{{.*}}: i64 {{{.*}}}) attributes {[[SPIR_FUNCCC]], [[LINKEXTERNAL]], {{.*}}}
// CHECK:         sycl.constructor @vec(%memspacecast, %[[ARG0]], %[[ARG1]], %[[ARG2]], %memspacecast_4, %memspacecast_5) {MangledFunctionName = @[[VEC_INITLIST_VEC_CTR:.*]]} : (memref<?x!sycl_vec_i64_16_, 4>, memref<?x!sycl_vec_i64_8_, 4>, memref<?x!sycl_vec_i64_4_, 4>, memref<?x!sycl_vec_i64_2_, 4>, memref<?xi64, 4>, memref<?xi64, 4>)
// CHECK:       func.func @[[VEC_INITLIST_VEC_CTR]](%{{.*}}: memref<?x!sycl_vec_i64_16_, 4> {{{.*}}}, %{{.*}}: memref<?x!sycl_vec_i64_8_, 4> {{{.*}}}, %{{.*}}: memref<?x!sycl_vec_i64_4_, 4> {{{.*}}}, %{{.*}}: memref<?x!sycl_vec_i64_2_, 4> {{{.*}}}, %{{.*}}: memref<?xi64, 4> {{{.*}}}, %{{.*}}: memref<?xi64, 4> {{{.*}}}) attributes {[[SPIR_FUNCCC]], [[LINKONCE]], {{.*}}}

// CHECK-LLVM-LABEL: define spir_func void @cons_10(
// CHECK-LLVM-SAME:                                 ptr addrspace(4) noundef align 64 dereferenceable(64) %[[ARG0:.*]], ptr addrspace(4) noundef align 32 dereferenceable(32) %[[ARG1:.*]], ptr addrspace(4) noundef align 16 dereferenceable(16) %[[ARG2:.*]], i64 noundef %{{.*}}, i64 noundef %{{.*}}) #[[FUNCATTRS]] {
// CHECK-LLVM:         call spir_func void @[[VEC_INITLIST_VEC_CTR:.*]](ptr addrspace(4) noundef align 64 dereferenceable_or_null(128) %{{.*}}, ptr addrspace(4) noundef align 64 dereferenceable(64) %[[ARG0]], ptr addrspace(4) noundef align 32 dereferenceable(32) %[[ARG1]], ptr addrspace(4) noundef align 16 dereferenceable(16) %[[ARG2]], ptr addrspace(4) noundef align 8 dereferenceable(8) %{{.*}}, ptr addrspace(4) noundef align 8 dereferenceable(8) %{{.*}})
// CHECK-LLVM:       define linkonce_odr spir_func void @[[VEC_INITLIST_VEC_CTR]](ptr addrspace(4) noundef align 64 dereferenceable_or_null(128) %{{.*}}, ptr addrspace(4) noundef align 64 dereferenceable(64) %{{.*}}, ptr addrspace(4) noundef align 32 dereferenceable(32) %{{.*}}, ptr addrspace(4) noundef align 16 dereferenceable(16) %{{.*}}, ptr addrspace(4) noundef align 8 dereferenceable(8) %{{.*}}, ptr addrspace(4) noundef align 8 dereferenceable(8) %{{.*}}) #[[FUNCATTRS]] {

extern "C" SYCL_EXTERNAL void cons_10(const sycl::long8 &A,
				      const sycl::long4 &B,
				      const sycl::long2 &C,
				      sycl::cl_long D,
				      sycl::cl_long E) {
  auto vec = sycl::long16{A, B, C, D, E};
}

// CHECK-LABEL: func.func @cons_11()
// CHECK-SAME:                       attributes {[[SPIR_FUNCCC]], [[LINKEXTERNAL]], {{.*}}}
// CHECK-DAG:     %[[C0_I8:.*]] = arith.constant 0 : i8
// CHECK-NEXT:    %[[ALLOCA:.*]] = memref.alloca() : memref<1x!sycl_vec_i32_4_>
// CHECK-NEXT:    %[[VAL0:.*]] = "polygeist.memref2pointer"(%[[ALLOCA]]) : (memref<1x!sycl_vec_i32_4_>) -> !llvm.ptr
// CHECK-NEXT:    %[[VAL1:.*]] = "polygeist.typeSize"() <{source = !sycl_vec_i32_4_}> : () -> index
// CHECK-NEXT:    %[[VAL2:.*]] = arith.index_cast %[[VAL1]] : index to i64
// CHECK-NEXT:    "llvm.intr.memset"(%[[VAL0]], %[[C0_I8]], %[[VAL2]]) <{isVolatile = false}> : (!llvm.ptr, i8, i64) -> ()

// CHECK-LLVM-LABEL:  define spir_func void @cons_11()
// CHECK-LLVM-SAME:                                    #[[FUNCATTRS]] {
// CHECK-LLVM:          %[[VAL1:.*]] = alloca %"class.sycl::_V1::vec.5", i64 1, align 16
// CHECK-LLVM:          call void @llvm.memset.p0.i64(ptr %[[VAL1]], i8 0, i64 16, i1 false)

extern "C" SYCL_EXTERNAL void cons_11() {
  auto vec = sycl::vec<sycl::cl_int, 4>{};
}

// Keep at the end.
// CHECK-LLVM: attributes #[[FUNCATTRS]] = { convergent mustprogress noinline norecurse nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "sycl-module-id"="{{.*}}/Test/Verification/sycl/constructors.cpp" "sycl-optlevel"="0" }
