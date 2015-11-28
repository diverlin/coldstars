
#define MACRO_READ_SERIALIZED_DATA \
    std::stringstream ss; \
    ss << data; \
    boost::archive::text_iarchive ia(ss); \
    ia >> *this;

#define MACRO_SAVE_SERIALIZED_DATA \
    std::stringstream ss; \
    boost::archive::text_oarchive oa(ss); \
    oa << *this; \
    return ss.str();

