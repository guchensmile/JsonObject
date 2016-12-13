# JsonObject
A warpper for [boost/property_tree](https://github.com/boostorg/property_tree) which is used Json parser readable.
It requires boost library containing property_tree.

# Ref
Some usage refer to [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

# Advantage
If you are using boost and don't want add additional library, it's will be helpful.

# Disadvantage
Not fully compliant to JSON
boost/property_tree parse everything as string; thus, null/empty array show as ""; int will show "int_value"

# More
http://json.org/



