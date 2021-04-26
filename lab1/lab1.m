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
    ylabel("number of iterations");
    ttle = {"number of iterations vs. precision", "("+filename(1)+")"};
    title(ttle);
    legend(names);
    exportgraphics(fig, path+strjoin(string(ttle)).replace(" ","_").replace("\","") + ".pdf", "ContentType", "vector");
    hold off;
    
    
    fig = figure;
    names = {};
    for i = 1:step:length(f)
        plot(s(i:i+step-1), fo(i:i+step-1), '.-');
        names{end + 1} = num2str(f(i));
        hold on;
    end
    grid();
    xlabel("approximation");
    ylabel("number of iterations");
    ttle = {"number of iterations vs. approximation", "("+filename(1)+")"};
    title(ttle);
    legend(names, "Location", "SouthEast");
    exportgraphics(fig, path+strjoin(string(ttle)).replace(" ","_").replace("\","") + ".pdf", "ContentType", "vector");
    hold off;
    
    fclose(p_bisect);
end
