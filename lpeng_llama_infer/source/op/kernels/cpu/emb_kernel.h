

#ifndef LPENG_LLAMA_INFER_INFER_EMB_KERNEL_H
#define LPENG_LLAMA_INFER_INFER_EMB_KERNEL_H
#include "base/base.h"
#include "tensor/tensor.h"
namespace kernel {
void emb_kernel_normal(const tensor::Tensor& input, const tensor::Tensor& weight,
                       const tensor::Tensor& output, int32_t vocab_size,
                       void* stream = nullptr);
}  // namespace kernel
#endif  // LPENG_LLAMA_INFER_INFER_EMB_KERNEL_H
