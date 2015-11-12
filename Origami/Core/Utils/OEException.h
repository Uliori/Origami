//
//  KEException.h
//  Katana
//
//  Created by Sephiroth on 5/21/14.
//  Copyright (c) 2014 Sephiroth. All rights reserved.
//

#ifndef __Origami__KEException__
#define __Origami__KEException__

#include <exception>
#include <string>

class OEException : public std::exception {
private:
    std::string m_msg;
public:
    OEException();
    OEException(const std::string& msg);
    
    virtual ~OEException();
    virtual const char *what();
    
};
#endif /* defined(__Katana__KEException__) */
