/*
 * Copyright 2019 - 2020 Elie Michel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** \file
 * \ingroup openmesheffect
 *
 */

#ifndef __MFX_ATTRIBUTES_H__
#define __MFX_ATTRIBUTES_H__

#include "properties.h"
#include "Collection.h"

#include <vector>
#include <string>
#include <utility>

namespace OpenMfx {

enum class AttributeAttachment {
  Invalid = -1,
  Point,
  Corner,
  Face,
  Mesh,
};

enum class AttributeType {
  Invalid = -1,
  UByte,  // kOfxMeshAttribTypeUByte
  Int,    // kOfxMeshAttribTypeInt
  Float,  // kOfxMeshAttribTypeFloat
};

}  // namespace OpenMfx

struct OfxAttributeStruct {
  using AttributeType = OpenMfx::AttributeType;
  using AttributeAttachment = OpenMfx::AttributeAttachment;

  OfxAttributeStruct();

  OfxAttributeStruct(const OfxAttributeStruct &) = delete;
  OfxAttributeStruct &operator=(const OfxAttributeStruct &) = delete;

  OfxAttributeStruct(OfxAttributeStruct &&) = default;
  OfxAttributeStruct &operator=(OfxAttributeStruct &&) = default;

  void set_name(const char *name);

  void deep_copy_from(const OfxAttributeStruct &other);

  AttributeType type();
  AttributeAttachment attachment() const
  {
    return m_attachment;
  }
  const std::string &name() const
  {
    return m_name;
  }

  bool copy_data_from(const OfxAttributeStruct &source, int start, int count);

  // For Collection
  using Index = std::pair<AttributeAttachment, std::string>;
  void setIndex(const Index &index);
  Index index() const;

 public:
  static AttributeAttachment attachmentAsEnum(const char *mfxAttachment);
  static AttributeType typeAsEnum(const char *mfxType);
  static int byteSizeOf(AttributeType type);

 public:
  OfxPropertySetStruct properties;

 private:
  std::string m_name;
  AttributeAttachment m_attachment = AttributeAttachment::Invalid;
};

struct OfxAttributeSetStruct : OpenMfx::Collection<OfxAttributeStruct> {
};

#endif // __MFX_ATTRIBUTES_H__
