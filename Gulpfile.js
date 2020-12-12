const gulp = require("gulp");

function copyInput() {
    return gulp.src("input/*.txt")
        .pipe(gulp.dest('cmake-build-debug/input')
        )
}

gulp.task('default', gulp.series(copyInput));