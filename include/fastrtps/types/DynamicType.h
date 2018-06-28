// Copyright 2018 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TYPES_DYNAMIC_TYPE_H
#define TYPES_DYNAMIC_TYPE_H

#include <fastrtps/types/MemberId.h>

namespace eprosima{
namespace fastrtps{
namespace types{

class AnnotationDescriptor;
class TypeDescriptor;
class DynamicTypeMember;

class DynamicType
{
public:
    DynamicType();
    DynamicType(const TypeDescriptor* descriptor);

    virtual ~DynamicType();

	ResponseCode get_descriptor(TypeDescriptor* descriptor) const;
	bool equals(const DynamicType* other) const;
	std::string get_name() const;
	TypeKind get_kind() const;

	ResponseCode get_member_by_name(DynamicTypeMember& member, const std::string name);
	ResponseCode get_all_members_by_name(std::map<std::string, DynamicTypeMember*>& members);

	ResponseCode get_member(DynamicTypeMember& member, MemberId id);
	ResponseCode get_all_members(std::map<MemberId, DynamicTypeMember*>& members);

	uint32_t get_annotation_count();
	ResponseCode get_annotation(AnnotationDescriptor& descriptor, uint32_t idx);

protected:

    friend class DynamicTypeBuilder;
    friend class DynamicTypeBuilderFactory;
    friend class MemberDescriptor;
    friend class TypeDescriptor;

    virtual void Clear();

    DynamicType(const DynamicType* other);

    ResponseCode copy_from_type(const DynamicType* other);

    TypeDescriptor* mDescriptor;
	std::vector<AnnotationDescriptor*> mAnnotation;
	std::map<MemberId, DynamicTypeMember*> mMemberById;         // Aggregated members
    std::map<std::string, DynamicTypeMember*> mMemberByName;    // Uses the pointers from "mMemberById".
    std::string mName;
	TypeKind mKind;
};

} // namespace types
} // namespace fastrtps
} // namespace eprosima

#endif // TYPES_DYNAMIC_TYPE_H