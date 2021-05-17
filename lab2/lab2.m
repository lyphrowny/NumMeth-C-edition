dir_name = "./gen_files";
path = "./images";
directory = dir(dir_name);
filenames = string(strcat(dir_name, "/", {directory(~[directory.isdir]).name})); % getting only files, excluding dirs

fig = figure;
for filename = filenames
    [mat, sol, res] = readMatrix(filename);
    disp(normError(sol, res));
    disp(cond(mat));
    semilogy(cond(mat), normError(sol, res), "*");
    hold on; 
end
grid on;
ttl = "solution error vs. cond number";
title(ttl);
ylabel("solution error");
xlabel("cond number");
exportgraphics(fig, strcat(path, "/", strjoin(string(ttl)).replace(" ","_").replace("\",""),".pdf"), "ContentType", "vector");
hold off;


function [mat, sol, res] = readMatrix(filename)
disp(filename);
    file = fopen(filename, 'r');
    
    lines = [];
    while ~feof(file)
        line = fgetl(file);
        if line
            lines = [lines string({line})];
        end
    end
    lines = lines';
    mat = str2double(lines(1:end-2).split());
    mat = mat(:, 1:end-1);
    sol = str2double(lines(end-1).split());
    res = lines(end).split();
    res = str2double(res(1:end - res.contains(""))); % remove the "" char at the end
        
    fclose(file);
end

function err = normError(sol, res)
    err = abs(norm(sol, Inf) -  norm(res, Inf));
end