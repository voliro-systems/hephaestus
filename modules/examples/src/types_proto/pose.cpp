//=================================================================================================
// Copyright (C) 2023-2024 HEPHAESTUS Contributors
//=================================================================================================

#include "hephaestus/examples/types_proto/pose.h"

#include "hephaestus/examples/types/pose.h"
#include "hephaestus/examples/types/proto/pose.pb.h"
#include "hephaestus/examples/types_proto/geometry.h"

namespace heph::examples::types {
void toProto(proto::Pose& proto_pose, const Pose& pose) {
  toProto(*proto_pose.mutable_position(), pose.position);
  toProto(*proto_pose.mutable_orientation(), pose.orientation);
}

void fromProto(const proto::Pose& proto_pose, Pose& pose) {
  fromProto(proto_pose.position(), pose.position);
  fromProto(proto_pose.orientation(), pose.orientation);
}

void toProto(proto::FramedPose& proto_pose, const FramedPose& pose) {
  proto_pose.set_frame(pose.frame);
  toProto(*proto_pose.mutable_pose(), pose.pose);
}

void fromProto(const proto::FramedPose& proto_pose, FramedPose& pose) {
  pose.frame = proto_pose.frame();
  fromProto(proto_pose.pose(), pose.pose);
}

}  // namespace heph::examples::types
