fileNames = ["p_bisect.txt", "p_secant.txt", "t_bisect.txt", "t_secant.txt"];
path = "./images/";

for file = fileNames
    disp(file);
    p_bisect = fopen(file, "r");
    filename = file.replace("_","\_").split(".");
    formatSpec = "%f;%f;%f;%f";
    p_bisect_size = [4 Inf];
    
    p_bisect_data = fscanf(p_bisect, formatSpec, p_bisect_size);
    
    f = p_bisect_data(1, :)';
    s= p_bisect_data(2, :)';
    fo =p_bisect_data(4, :)';
    
    step = 14;
    
    fig = figure;
    names = {};
    for i = 1:step:length(f)
        semilogx(f(i:i+step-1), fo(i:i+step-1), '.-');
        names{end + 1} = num2str(f(i));
        hold on;
    end
    grid();
    xlabel("precision");
    ylabel("iterations");
    ttle = {"iterations vs. precision", "("+filename(1)+")"};
    title(ttle);
    legend(names);
    exportgraphics(fig, path+strjoin(string(ttle)).replace(" ","_").replace("\","") + ".pdf", "ContentType", "vector");
    hold off;
    
    
    fig = figure;
    names = {};
    for i = 1:step:length(f)
        semilogx(s(i:i+step-1), fo(i:i+step-1), '.-');
        names{end + 1} = num2str(f(i));
        hold on;
    end
    grid();
    xlabel("offset");
    ylabel("iterations");
    ttle = {"iterations vs. offset", "("+filename(1)+")"};
    title(ttle);
    legend(names, "Location", "NorthWest");
    exportgraphics(fig, path+strjoin(string(ttle)).replace(" ","_").replace("\","") + ".pdf", "ContentType", "vector");
    hold off;
    
    fclose(p_bisect);
end

joint_filenames = ["p_bi_se_off.txt", "t_bi_se_off.txt"];
for file = joint_filenames
    disp(file);
    p_bisect = fopen(file, "r");
    filename = file.replace("_","\_").split(".");
    formatSpec = "%f;%f;%f;%f";
    p_bisect_size = [4 Inf];
    
    p_bisect_data = fscanf(p_bisect, formatSpec, p_bisect_size);
    
    bi = p_bisect_data(:, 1:2:end)';
    se = p_bisect_data(:, 2:2:end)';
    
    bi_off = bi(:, 2);
    bi_it = bi(:, 4);
    
    se_off = se(:, 2);
    se_it = se(:, 4);

    fig = figure;
    semilogx(bi_off, bi_it, '.-');
    hold on;
    semilogx(se_off, se_it, '.-');
    grid();
    xlabel("offset");
    ylabel("iterations");
    ttle = {"iterations vs. offset", "("+filename(1)+")"};
    title(ttle);
    legend(["bisect", "secant"]);
    exportgraphics(fig, path+strjoin(string(ttle)).replace(" ","_").replace("\","") + ".pdf", "ContentType", "vector");
    hold off;
    
    fclose(p_bisect);
end

joint_filenames =  ["p_bi_se_prec.txt", "t_bi_se_prec.txt"];
for file = joint_filenames
    disp(file);
    p_bisect = fopen(file, "r");
    filename = file.replace("_","\_").split(".");
    formatSpec = "%f;%f;%f;%f";
    p_bisect_size = [4 Inf];
    
    p_bisect_data = fscanf(p_bisect, formatSpec, p_bisect_size);
    
    bi = p_bisect_data(:, 1:2:end)';
    se = p_bisect_data(:, 2:2:end)';
    
    bi_prec = bi(:, 1);
    bi_it = bi(:, 4);
    
    se_prec = se(:, 1);
    se_it = se(:, 4);

    fig = figure;
    semilogx(bi_prec, bi_it, '.-');
    hold on;
    semilogx(se_prec, se_it, '.-');
    grid();
    xlabel("precision");
    ylabel("iterations");
    ttle = {"iterations vs. precision", "("+filename(1)+")"};
    title(ttle);
    legend(["bisect", "secant"]);
    exportgraphics(fig, path+strjoin(string(ttle)).replace(" ","_").replace("\","") + ".pdf", "ContentType", "vector");
    hold off;
    
    fclose(p_bisect);
end