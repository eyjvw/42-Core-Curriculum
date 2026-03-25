FROM oven/bun:1.1

WORKDIR /app

COPY backend/auth/config/package.json backend/auth/config/bun.lock ./
RUN bun install

COPY backend/auth/src ./src
COPY backend/db ./db

RUN mkdir -p /app/data

EXPOSE 4000

CMD ["bun", "run", "src/index.ts"]
