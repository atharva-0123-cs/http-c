#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>      // <<<<< add this
#include <inttypes.h>    // <<<<< add this
#include <cmocka.h>
#include "network.h"
#include <arpa/inet.h>

/* Test addr_to_str() for IPv4 */
static void test_addr_to_str_ipv4(void **state) {
    (void) state;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));

    char result[INET6_ADDRSTRLEN];
    addr_to_str((struct sockaddr*)&addr, result);

    assert_string_equal(result, "127.0.0.1");
}

/* Test addr_to_str() for IPv6 */
static void test_addr_to_str_ipv6(void **state) {
    (void) state;
    struct sockaddr_in6 addr6;
    addr6.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &(addr6.sin6_addr));

    char result[INET6_ADDRSTRLEN];
    addr_to_str((struct sockaddr*)&addr6, result);

    assert_string_equal(result, "::1");
}

/* Main entry for CMocka */
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_addr_to_str_ipv4),
        cmocka_unit_test(test_addr_to_str_ipv6),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
