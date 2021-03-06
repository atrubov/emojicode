//
//  Options.hpp
//  EmojicodeCompiler
//
//  Created by Theo Weidmann on 25/08/2017.
//  Copyright © 2017 Theo Weidmann. All rights reserved.
//

#ifndef Options_hpp
#define Options_hpp

#include "../../EmojicodeShared.h"
#include "../Application.hpp"
#include <memory>
#include <string>

namespace EmojicodeCompiler {

namespace CLI {

/// An instance of this class represents the command-line options with which the compiler was started.
class Options {
public:
    /// Constructs an Options instance from the command-line arguments and environment variables.
    Options(int argc, char *argv[]);

    /// Whether the compilation should begin at all. False, if the options are invalid or the version was printed.
    bool beginCompilation() const { return beginCompilation_; }

    /// This method must be used to print messages or errors about the command-line interface use.
    void printCliMessage(const std::string &message);

    /// @returns An ApplicationDelegate that matches the options represented by the instance.
    std::unique_ptr<ApplicationDelegate> applicationDelegate();

    const std::string& packageToReport() const { return packageToReport_; }
    const std::string& outPath() const { return outPath_; }
    const std::string& mainFile() const { return mainFile_; }
    const std::string& sizeVariable() const { return sizeVariable_; }
    const std::string& packageDirectory() const { return packageDirectory_; }
    const std::string& migrationFile() const { return migrationFile_; }

    /// Whether the main purpose of the invocation of the compiler is to prettyprint a file.
    /// This method returns true if prettyprint was explicitely requested or if a file is being migrated.
    const bool prettyprint() const { return format_; }
private:
    std::string packageToReport_;
    std::string outPath_;
    std::string mainFile_;
    std::string sizeVariable_;
    std::string packageDirectory_ = defaultPackagesDirectory;
    std::string migrationFile_;
    bool format_ = false;
    bool jsonOutput_ = false;
    bool beginCompilation_ = true;

    void readEnvironment();
    void parsePositionalArguments(int positionalArguments, char *argv[]);
    /// If the file ends in ".emojimig", the migration file migrationFile_ will be set to it and prettyprint_ to true.
    /// The main file is then derived from by replacing ".emojimig" with ".emojic".
    void examineMainFile();
};

}  // namespace CLI

}  // namespace EmojicodeCompiler

#endif /* Options_hpp */
