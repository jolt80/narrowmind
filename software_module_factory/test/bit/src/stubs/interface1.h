/* Copyright Ericsson AB
 ***********************************************************************************
 *                                                                                 *
 * The copyright to the computer programs herein is the property of Ericsson AB.   *
 * The programs may be used and/or copied only with the written permission from    *
 * Ericsson AB or in accordance with the terms conditions stipulated in the        *
 * agreement/contract under which the programs have been supplied.                 *
 *                                                                                 *
 ***********************************************************************************
 */
#ifndef TEST_SRC_STUBS_INTERFACE1_H_
#define TEST_SRC_STUBS_INTERFACE1_H_

namespace config {
namespace server {

class Interface1 {
 public:
  Interface1() = default;
  virtual ~Interface1() = default;

  virtual void interface1Method() = 0;
};

}  // namespace server
}  // namespace config

#endif /* TEST_SRC_STUBS_INTERFACE1_H_ */
