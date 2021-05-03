gen_data = "./gen_data";
gen_files = "./gen_files";

prec_ = strcat(gen_data, "/prec.txt");
sols_ = strcat(gen_data, "/sols.txt");
gen_sols_ = strcat(gen_files, "/gen_sols.txt");
mat_ = strcat(gen_files, "/gen_mat.txt");

path = "./images";

lines = readFile(sols_).split();
params = str2double(lines(:, 1));
sols = str2double(lines(:, 2:end-1));

lines = readFile(prec_).split();
prec = str2double(lines(:, 1));
iters = str2double(lines(:, 2));

lines = readFile(gen_sols_).split();
det = str2double(lines(:, 2));
gen_sols = str2double(lines(:, 3:end));

lines = readFile(mat_).split();
mat = str2double(lines(:, 1:end-1));
b = str2double(lines(:, end));

params = params';
det = det';

fig = figure;
norms = [];
for i = 1:size(gen_sols, 1)
    norms = [norms, abs(norm(sols(i, :)) - norm(gen_sols(i, :)))];
end
loglog(norms, det, '*-');
grid on;
ttl = "determinant vs. solution error";
title(ttl);
xlabel("solution error");
ylabel("determinant");
exportgraphics(fig, strcat(path, "/", strjoin(string(ttl)).replace(" ","_").replace("\",""),".pdf"), "ContentType", "vector");
hold off;

fig = figure;
semilogy(iters, prec, '*-');
grid on;
ttl = "iterations vs. precison";
title(ttl);
xlabel("iterations");
ylabel("precision");
exportgraphics(fig, strcat(path, "/", strjoin(string(ttl)).replace(" ","_").replace("\",""),".pdf"), "ContentType", "vector");
hold off;

function lines = readFile(filename) 
    file = fopen(filename, "r");

    lines = [];
    while ~feof(file)
        line = fgetl(file);
        if line
            lines = [lines string({line})];
        end
    end
    lines = lines';
    fclose(file);
end