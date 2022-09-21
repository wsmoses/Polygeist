#ifndef POLYGEIST_DIALECT_POLYGEIST_PASSES_H
#define POLYGEIST_DIALECT_POLYGEIST_PASSES_H

#include "mlir/Conversion/LLVMCommon/LoweringOptions.h"
#include "mlir/Pass/Pass.h"
#include <memory>
namespace mlir {
class PatternRewriter;
class RewritePatternSet;
class DominanceInfo;
namespace polygeist {
std::unique_ptr<Pass> createParallelLICMPass();
std::unique_ptr<Pass> createMem2RegPass();
std::unique_ptr<Pass> createLoopRestructurePass();
std::unique_ptr<Pass> createInnerSerializationPass();
std::unique_ptr<Pass> createSerializationPass();
std::unique_ptr<Pass> replaceAffineCFGPass();
std::unique_ptr<Pass> createOpenMPOptPass();
std::unique_ptr<Pass> createCanonicalizeForPass();
std::unique_ptr<Pass> createRaiseSCFToAffinePass();
std::unique_ptr<Pass> createCPUifyPass(StringRef method = "");
std::unique_ptr<Pass> createBarrierRemovalContinuation();
std::unique_ptr<Pass> detectReductionPass();
std::unique_ptr<Pass> createRemoveTrivialUsePass();
std::unique_ptr<Pass> createParallelLowerPass();
std::unique_ptr<Pass>
createConvertGpuModulePolygeistToLLVMPass(const LowerToLLVMOptions &options);
std::unique_ptr<Pass>
createConvertPolygeistToLLVMPass(const LowerToLLVMOptions &options,
                                 bool useCStyleMemRef);
std::unique_ptr<Pass> createConvertPolygeistToLLVMPass();
std::unique_ptr<Pass> createConvertGpuModulePolygeistToLLVMPass();
std::unique_ptr<Pass> createForBreakToWhilePass();
std::unique_ptr<Pass> createRemoveDeviceFunctionsPass();
std::unique_ptr<Pass> createConvertParallelToGPUPass();

void populateForBreakToWhilePatterns(RewritePatternSet &patterns);
} // namespace polygeist
} // namespace mlir

void fully2ComposeAffineMapAndOperands(
    mlir::PatternRewriter &rewriter, mlir::AffineMap *map,
    llvm::SmallVectorImpl<mlir::Value> *operands, mlir::DominanceInfo &DI);
bool isValidIndex(mlir::Value val);

namespace mlir {
// Forward declaration from Dialect.h
template <typename ConcreteDialect>
void registerDialect(DialectRegistry &registry);

namespace arith {
class ArithDialect;
} // end namespace arith

namespace scf {
class SCFDialect;
} // end namespace scf

namespace memref {
class MemRefDialect;
} // end namespace memref

namespace func {
class FuncDialect;
}

class AffineDialect;
namespace LLVM {
class LLVMDialect;
}

#define GEN_PASS_REGISTRATION
#include "polygeist/Passes/Passes.h.inc"

} // end namespace mlir

#endif // POLYGEIST_DIALECT_POLYGEIST_PASSES_H
