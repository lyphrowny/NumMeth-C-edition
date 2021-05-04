dir_name = "./gen_data";
path = "./images";
directory = dir(dir_name);
filenames = string(strcat(dir_name, "/", {directory(~[directory.isdir]).name})); % getting only files, excluding dirs

for filename = filenames
    fig = figure;
    [tol, eig, it] = readFile(filename);
    semilogy(it, tol, "*-");
    grid on;
    info = filename.split('_');
    ttl = strcat("tolerance vs. iterations (", info(end).replace(".txt",""), " separability)");
    title(ttl);
    xlabel("iterations");
    ylabel("tolerance");
    exportgraphics(fig, strcat(path, "/", strjoin(string(ttl)).replace(" ","_").replace("\",""),".pdf"), "ContentType", "vector");
end

function [tol, eig, it] = readFile(filename)
    file = fopen(filename, 'r');
    
    lines = [];
    while ~feof(file)
        line = fgetl(file);
        if line
            lines = [lines string({line})];
        end
    end
    lines = str2double(lines.split());
    tol = lines(:, :, 1);
    eig = lines(:, :, 2);
    it = lines(:, :, 3);
        
    fclose(file);
end