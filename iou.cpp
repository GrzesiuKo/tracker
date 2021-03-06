#include "iou.hpp"

bool IOU::iou_cmp(const IOU& a, const IOU& b)
{
    return a.value > b.value;
}

void IOU::print() const
{
    std::cout << "frame: " << start_frame << ", id1: " << detection_id1 << ", id2: " << detection_id2
              << ", value: " << value << std::endl;
}
