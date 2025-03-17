# ASSIGNMENT 1: BITOPS, NUMBER REPRESENTATIONS, AND RELATED APPLICATIONS

## INTRODUCTION
In Assignment 1, we need to understand several floating point formats. Different from [IEEE 754](https://en.wikipedia.org/wiki/IEEE_754) which occupies 4 bytes to represent floating points, [binary16](https://en.wikipedia.org/wiki/Half-precision_floating-point_format), and [bfloat16](https://en.wikipedia.org/wiki/Bfloat16_floating-point_format), both occupy 2-byte, and are proper for some scenario, such as Graphic Processing and Machine Learning.

However, originally obtained floating-point data are not always in bfloat16 or binary16, so some tools are needed to perform the conversions. Implementations of these conversion tools rely on the BITwise OPerationS (bitops) toward these different floating-point formats. On the other hand, bitops is the fundamental instructions supported by microprocessors. It is worth learning bitops for efficient programming skills.

In addition to the floating-point data conversion, bitops can be applied to many applications. For the efficiency bitops provide, some hardware support dedicated instructions, such as count leading zeros (clz) or [find first set (ffs)](https://en.wikipedia.org/wiki/Find_first_set), which are involved in these applications. Thus, experience the programming skills derived from bitops now!

