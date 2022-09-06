#include <iostream>
#include <string.h>
#include <openssl/md5.h>
#include <algorithm>
#include <vector>
#include <optional>

struct OperatorRoleAndName {
    std::string id;
    std::string operator_name;
    std::optional<std::string> operator_role;
};
struct SafetyData {
    std::vector<std::string> monitored_workplaces;
    std::optional<OperatorRoleAndName> safety_data_operator;
    std::string operator_position_id;
    std::string operator_position_status;
    int64_t sequence_number;
};


std::string GenerateMD5Hash(const std::string& input) {
  unsigned char md5_value[MD5_DIGEST_LENGTH];
  MD5((unsigned char *)input.data(), input.size(), md5_value);

  char md5_hex[2 * MD5_DIGEST_LENGTH];
  for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
    std::sprintf(md5_hex + 2 * i, "%02x", md5_value[i]);  // NOLINT
  }

  return std::string{md5_hex};
}

std::string GetNormalizedSafetyData(SafetyData safety_data) {
  std::string safety_data_str =
    safety_data.operator_position_id +
    safety_data.operator_position_status;

  if (safety_data.safety_data_operator) {
    safety_data_str +=
      safety_data.safety_data_operator->id +
      safety_data.safety_data_operator->operator_name;
      if (safety_data.safety_data_operator->operator_role) {
        safety_data_str +=
          safety_data.safety_data_operator->operator_role.value();
      }
  }

  std::sort(safety_data.monitored_workplaces.begin(), safety_data.monitored_workplaces.end());
  for (auto workplace_id : safety_data.monitored_workplaces) {
    // cppcheck-suppress useStlAlgorithm
    safety_data_str += workplace_id;
  }

  safety_data_str += std::to_string(safety_data.sequence_number);

  return safety_data_str;
}
std::string Uppercase(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::toupper(c); });
  return str;
}

std::string GenerateSafetyDataMD5Hash(SafetyData safety_data) {
  return Uppercase(GenerateMD5Hash(GetNormalizedSafetyData(safety_data)));
}


//-------------------------------------------------------------------------------
int main() {
  SafetyData safety_data;
  safety_data.operator_position_id = "ffd5b90e-0a0a-4c25-a27c-56e58b5dfebc";
  safety_data.operator_position_status = "OK";

  safety_data.safety_data_operator.emplace();
  safety_data.safety_data_operator->id = "ffd5b90e-0a0a-4c25-a27c-56e58b5dfebc";
  safety_data.safety_data_operator->operator_name = "James Noris";
  safety_data.safety_data_operator->operator_role.emplace();
  safety_data.safety_data_operator->operator_role = "Monitoring Operator";

  safety_data.monitored_workplaces = {"d335b90e-0a0a-4c25-a27c-7be58b5dfe9a", "c763f0f4-9c53-43f8-b7a5-abc3f16b6a6e"};
  safety_data.sequence_number = 123;

  std::cout << GenerateSafetyDataMD5Hash(safety_data) << "\n";

  return 0;
}
