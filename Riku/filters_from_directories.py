# Kacper Walasek
import os

def _process_directory(prefix, path):
    dirs = os.listdir(prefix + path)
    filters = ''
    cpps = ''
    hs = ''
    for file in dirs:
        filter, cpp, h= _process_file(prefix,path,file)
        filters += filter
        cpps += cpp
        hs += h
    return filters, cpps, hs

def _process_file(prefix,path,name):
    if os.path.isdir(prefix + path + '/' + name):
        inFilters, inCpp, inH = _process_directory(prefix, path+'\\'+ name)
        return '\t\t<Filter Include=\"Riku' + path + '\\' + name +'\"></Filter>\n'+inFilters, inCpp, inH
    else:
        path_without_slash = path[1:] + '\\' if len(path)!=0 else ''
        plik = "Include=\"..\\src\\" + path_without_slash + name + "\"> \n \t\t\t<Filter>Riku" + path + "</Filter> \n\t\t"
        if os.path.splitext(name)[1] == '.h':
            return '','','\t\t<ClInclude ' + plik + '</ClInclude>\n'
        elif os.path.splitext(name)[1] == '.cpp':
            return '','\t\t<ClCompile ' + plik + '</ClCompile>\n',''
        else:
            return '','',''


if __name__ == "__main__":
    filters, cpps, hs =  _process_directory('./src','')

    print('<?xml version="1.0" encoding="utf-8"?>\n' 
        + '<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">\n'
        + '\t<ItemGroup>\n'
        + '\t\t<Filter Include=\"Riku\"></Filter>\n'
        + filters
        + '\t</ItemGroup>\n'
        + '\t<ItemGroup>\n'
        + cpps
        + '\t</ItemGroup>\n'
        + '\t<ItemGroup>\n'
        + hs
        + '\t</ItemGroup>\n'
        + '</Project>'
    )